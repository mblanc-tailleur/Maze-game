#pragma once
#include <SFML/System/Vector2.hpp>
#include "Entity.h"

class Collider
{
public:
	virtual Entity::CollidingSide IsColliding(Collider* pOther) = 0;

	virtual void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) = 0;
	virtual sf::Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) = 0;

	virtual void Move(sf::Vector2f translation) = 0;
};