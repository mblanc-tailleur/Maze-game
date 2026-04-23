#include "CircleCollider.h"
#include "AABBCollider.h"

#include <iostream>

Entity::CollidingSide CircleCollider::IsColliding(Collider* pOther)
{
    //Circle vs Circle Collision
	if (CircleCollider* otherCircle = dynamic_cast<CircleCollider*> (pOther))
	{
		sf::Vector2f distance = GetPosition(0.5f, 0.5f) - otherCircle->GetPosition(0.5f, 0.5f);

		float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

		float radius1 = mRadius;
		float radius2 = otherCircle->mRadius;

		float sqrRadius = (radius1 + radius2) * (radius1 + radius2);

		if (sqrLength < sqrRadius)
		{
			bool a = true;
		}
		if (sqrLength < sqrRadius)
			return Entity::Other;
	}
    //Circle vs AABB collision
	else if (AABBCollider* otherAABB = dynamic_cast<AABBCollider*>(pOther))
	{
		float testX = GetPosition().x;
		float testY = GetPosition().y;

		if (mX < otherAABB->mXMin)
			testX = otherAABB->mXMin;
		else if (mX > otherAABB->mXMax)
			testX = otherAABB->mXMax;

		if (mY < otherAABB->mYMin)
			testY = otherAABB->mYMin;
		else if (mY > otherAABB->mYMax)
			testY = otherAABB->mYMax;

		sf::Vector2f distanceVector = sf::Vector2f(mX, mY) - sf::Vector2f(testX, testY);

		float distance = (distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y);

		if (distance < mRadius)
			return Entity::Other;
	}

    return Entity::None;
}

void CircleCollider::SetPosition(float x, float y, float anchorX, float anchorY)
{
	mX = x - anchorX * mRadius;
	mY = y - anchorY * mRadius;
}

sf::Vector2f CircleCollider::GetPosition(float anchorX, float anchorY)
{
	return sf::Vector2f(mX + anchorX * mRadius, mY + anchorY * mRadius);
}

void CircleCollider::Move(sf::Vector2f translation)
{
	mX += translation.x;
	mY += translation.y;
}
