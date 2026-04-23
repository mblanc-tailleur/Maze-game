#include "Entity.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::CreateRectangle(float width, float height, const sf::Color& color, Collider* collider)
{
	return GetScene()->CreateRectangle<T>(width, height, color, collider);
}

template<typename T>
T* Entity::CreateCircle(float radius, float outlineThickness, const sf::Color& color, Collider* collider)
{
	return GetScene()->CreateCircle<T>(radius, outlineThickness, color, collider);
}

template<typename T>
T* Entity::CreateSprite(float width, float height, const char* texturePath, Collider* collider)
{


	return GetScene()->CreateSprite<T>(width, height, texturePath, collider);
}