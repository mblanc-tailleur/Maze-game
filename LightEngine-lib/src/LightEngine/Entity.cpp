#include "Entity.h"

#include "GameManager.h"
#include "AssetManager.h"
#include "Utils.h"
#include "Debug.h"
#include "AABBCollider.h"
#include "CircleCollider.h"
#include <iostream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Entity::Initialize(float width, float height, sf::RectangleShape* shape, const sf::Color& color, Collider* collider)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mDrawable = shape;
	mTransformable = shape;

	mTransformable->setOrigin(0.f, 0.f);
	((sf::Shape*)mDrawable)->setFillColor(color);

	((sf::RectangleShape*)mTransformable)->setSize(sf::Vector2f(width, height));

	mWidth = width;
	mHeight = height;
	
	mCollider = collider;
	
	mTarget.isSet = false;

	Initialize();
	OnInitialize();
}

void Entity::Initialize(float radius, sf::CircleShape* shape, const sf::Color& color, Collider* collider)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mDrawable = shape;
	mTransformable = shape;

	mTransformable->setOrigin(0.f, 0.f);
	((sf::Shape*)mDrawable)->setFillColor(color);

	((sf::CircleShape*)mTransformable)->setRadius(radius / 2);

	mWidth = radius * 2;
	mHeight = radius * 2;
	
	mCollider = collider;
	
	mTarget.isSet = false;

	Initialize();
	OnInitialize();
}

void Entity::Initialize(float width, float height, const char* texturePath, Collider* collider)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	sf::Sprite* sprite = new sf::Sprite(*AssetManager::Get()->GetTexture(texturePath));
	sf::FloatRect rect = sprite->getGlobalBounds();

	float ratioX = width / rect.width;
	float ratioY = height / rect.height;
	float ratioMin = std::min(ratioX, ratioY);

	sprite->setScale(ratioMin, ratioMin);

	mDrawable = sprite;
	mTransformable = sprite;
	
	mWidth = ratioMin * rect.width;
	mHeight = ratioMin * rect.height;
	mCollider = collider;
	
	mTarget.isSet = false;

	Initialize();
	OnInitialize();
}

void Entity::Repulse(Entity* other, CollidingSide collidingSide) 
{
	Collider* otherCollider = other->GetCollider();

	if (dynamic_cast<CircleCollider*> (mCollider) && dynamic_cast<CircleCollider*> (otherCollider))
	{
		sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

		float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
		float length = std::sqrt(sqrLength);

		float radius1 = GetRadius();
		float radius2 = other->GetRadius();

		float overlap = (length - (radius1 + radius2)) * 0.5f;

		sf::Vector2f normal = distance / length;

		sf::Vector2f translation = overlap * normal;

		sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
		sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

		SetPosition(position1.x, position1.y, 0.5f, 0.5f);
		other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
	}
	else if (dynamic_cast<AABBCollider*>(mCollider) && dynamic_cast<AABBCollider*> (otherCollider))
	{
		sf::Vector2f normal = { 0, 0 };
		float overlap = 0.f;

		//Touched side
		switch (collidingSide)
		{
		case Bottom:
			overlap = ((AABBCollider*)mCollider)->mYMax - ((AABBCollider*)otherCollider)->mYMin;
			normal = { 0, -1 };
			break;
		case Top:
			overlap = ((AABBCollider*)otherCollider)->mYMax - ((AABBCollider*)mCollider)->mYMin;
			normal = { 0, 1 };
			break;
		case Right:
			overlap = ((AABBCollider*)mCollider)->mXMax - ((AABBCollider*)otherCollider)->mXMin;
			normal = { -1, 0 };
			break;
		case Left:
			overlap = ((AABBCollider*)otherCollider)->mXMax - ((AABBCollider*)mCollider)->mXMin;
			normal = { 1, 0 };
			break;
		}

		sf::Vector2f translation = overlap * normal;

		sf::Vector2f position1 = GetPosition(0.5f, 0.5f) + translation;
		sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) - translation;

		if (other->IsStatic() == false && IsStatic() == false)
		{
			SetPosition(position1.x, position1.y, 0.5f, 0.5f);
			other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
		}
		else if (other->IsStatic())
		{
			SetPosition(position1.x, position1.y, 0.5f, 0.5f);
		}
		else if (IsStatic())
		{
			other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
		}
	}
}

Entity::CollidingSide Entity::IsColliding(Entity* other) const 
{
	if (mCollider == nullptr || other->mCollider == nullptr)
	{
		return None;
	}

	return mCollider->IsColliding(other->GetCollider());
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	sf::Vector2i mapPos = (sf::Vector2i)position;

	GameManager::Get()->mpWindow->mapPixelToCoords(mapPos);

	float dx = x - mapPos.x;
	float dy = y - mapPos.y;

	float radius = GetRadius();

	return (dx * dx + dy * dy) < (radius * radius);
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetScale(float ratioX, float ratioY)
{
	mTransformable->setScale(ratioX, ratioY);

	mWidth *= ratioX;
	mHeight *= ratioY;
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	x -= mWidth * ratioX;
	y -= mHeight * ratioY;

	mTransformable->setPosition(sf::Vector2f(x, y));

	sf::Vector2f currentPosition = GetPosition(0.5f, 0.5f);
	if (mCollider != nullptr)
		mCollider->SetPosition(currentPosition.x, currentPosition.y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position;

	position = mTransformable->getPosition();

	position.x += mWidth * ratioX;
	position.y += mHeight * ratioY;

	return position;
}

sf::Shape* Entity::GetShape()
{
	if (dynamic_cast<sf::CircleShape*> (mDrawable) != nullptr)
	{
		return ((sf::CircleShape*)mDrawable);
	}
	else if (dynamic_cast<sf::RectangleShape*> (mDrawable) != nullptr)
	{
		return ((sf::RectangleShape*)mDrawable);
	}
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	sf::Vector2i worldPos = sf::Vector2i(x, y);

	if (GoToDirection(worldPos.x, worldPos.y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { worldPos.x, worldPos.y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, worldPos.x, worldPos.y);
	mTarget.isSet = true;

	return true;
}


void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{
	OnUpdate();
}

void Entity::FixedUpdate(float fixedDt)
{
	float dt = fixedDt;
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	mTransformable->move(translation);

	
	if (mCollider != nullptr)
	{
		sf::Vector2f currentPosition = GetPosition(0.5f, 0.5f);
		mCollider->SetPosition(currentPosition.x, currentPosition.y);
	}

	/*if (AABBCollider* rectCollider = dynamic_cast<AABBCollider*> (mCollider))
		Debug::DrawRectangle(rectCollider->mXMin, rectCollider->mYMin, rectCollider->mWidth, rectCollider->mHeight, sf::Color::Green);*/

	if (mTarget.isSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		//Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		//Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}