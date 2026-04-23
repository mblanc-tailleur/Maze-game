#pragma once
#include "Collider.h"

class CircleCollider :
	public Collider
{
public:
	float mX = 0;
	float mY = 0;

	float mRadius = 0;

	CircleCollider(float radius) :
		mRadius(radius) {}

	Entity::CollidingSide IsColliding(Collider* pOther) override;

	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;

	sf::Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;

	void Move(sf::Vector2f translation) override;
};