#pragma once
#include "Collider.h"

class AABBCollider :
    public Collider
{
public:
    float mXMin = 0;
    float mYMin = 0;

    float mXMax = 0;
    float mYMax = 0;

    float mWidth;
    float mHeight;

    AABBCollider(float width, float height) :
        mWidth(width), mHeight(height) {}

    Entity::CollidingSide IsColliding(Collider* pOther) override;

    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
    sf::Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;

    void Move(sf::Vector2f translation) override;
};