#include "AABBCollider.h"
#include "CircleCollider.h"

#include <iostream>

Entity::CollidingSide AABBCollider::IsColliding(Collider* pOther)
{
    // AABB vs AABB Collision
    if (AABBCollider* otherAABB = dynamic_cast<AABBCollider*>(pOther))
    {
        // X
        bool IsPastLeftEdge = mXMax > otherAABB->mXMin;
        bool IsBeforeRightEdge = mXMin < otherAABB->mXMax;

        // Y
        bool IsPastUpperEdge = mYMax > otherAABB->mYMin;
        bool IsBeforeBottomEdge = mYMin < otherAABB->mYMax;

        if (IsPastLeftEdge == false || IsBeforeRightEdge == false || IsPastUpperEdge == false || IsBeforeBottomEdge == false)
            return Entity::CollidingSide::None;

        float maxMinX = std::max(mXMin, otherAABB->mXMin);
        float minMaxX = std::min(mXMax, otherAABB->mXMax);

        float overlapX = maxMinX - minMaxX;

        float maxMinY = std::max(mYMin, otherAABB->mYMin);
        float minMaxY = std::min(mYMax, otherAABB->mYMax);

        float overlapY = maxMinY - minMaxY;

        if (overlapY <= overlapX)
        {
            // X
            bool leftSide = mXMax < otherAABB->mXMax;

            if (leftSide)
                return Entity::CollidingSide::Right;
            else
                return Entity::CollidingSide::Left;
        }
        else if (overlapX < overlapY)
        {
            // Y
            bool topSide = mYMax < otherAABB->mYMax;


            if (topSide)
                return Entity::CollidingSide::Bottom;
            else
                return Entity::CollidingSide::Top;
        }
    }

    // AABB vs Circle Collision
    if (CircleCollider* otherCircle = dynamic_cast<CircleCollider*>(pOther))
    {
        float testX = otherCircle->mX;
        float testY = otherCircle->mY;

        if (otherCircle->mX < mXMin)
            testX = mXMin;
        else if (otherCircle->mX > mXMax)
            testX = mXMax;

        if (otherCircle->mY < mYMin)
            testY = mYMin;
        else if (otherCircle->mY > mYMax)
            testY = mYMax;

        sf::Vector2f distanceVector = sf::Vector2f(otherCircle->mX, otherCircle->mY) - sf::Vector2f(testX, testY);

        float distance = (distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y);

        if (distance < otherCircle->mRadius)
            return Entity::CollidingSide::Other;
    }

    return Entity::CollidingSide::None;
}

void AABBCollider::SetPosition(float x, float y, float anchorX, float anchorY)
{
    mXMin = x - mWidth * anchorX;
    mXMax = x + mWidth - mWidth * anchorX;

    mYMin = y - mHeight * anchorY;
    mYMax = y + mHeight - mHeight * anchorY;
}

sf::Vector2f AABBCollider::GetPosition(float anchorX, float anchorY)
{
    return sf::Vector2f(mXMin + anchorX * mWidth, mYMin + anchorY * mHeight);
}

void AABBCollider::Move(sf::Vector2f translation)
{
    mXMin += translation.x;
    mXMax += translation.x;

    mYMin += translation.y;
    mYMax += translation.y;
}