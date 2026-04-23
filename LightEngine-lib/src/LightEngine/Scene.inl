	#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"

template<typename T>
T* Scene::CreateRectangle(float width, float height, const sf::Color& color, Collider* collider)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));

	Entity* entity = newEntity;
	entity->Initialize(width, height, shape, color, collider);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
T* Scene::CreateCircle(float radius, const sf::Color& color, Collider* collider)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	sf::CircleShape* shape = new sf::CircleShape(radius);

	Entity* entity = newEntity;
	entity->Initialize(radius, shape, color, collider);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
T* Scene::CreateSprite(float width, float height, const char* texturePath, Collider* collider)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T;

	Entity* entity = newEntity;
	entity->Initialize(width, height, texturePath, collider);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}