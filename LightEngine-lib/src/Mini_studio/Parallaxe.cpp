#include "Parallaxe.h"
#include "Player.h"
#include "MainScene.h"
#include "GameManager.h"

void Parallaxe::Init(MainScene* scene, float gap)
{
    mPlayer = scene->GetPlayer();
    mActualScene = scene;
    mGap = gap;

    if (mPlayer != nullptr)
    {
        mPreviousPlayerPos = mPlayer->GetPosition();
        mInitialized = true;
    }
 
}

void Parallaxe::OnUpdate()
{

    if (!mActualScene) return;

    if (!mPlayer)
    {
        mPlayer = mActualScene->GetPlayer();
        mPreviousPlayerPos = mPlayer->GetPosition();
        return;
    }
    if (!mInitialized || !mPlayer) return;

    sf::Vector2f currentPos = mPlayer->GetPosition();

    float deltaX = currentPos.x - mPreviousPlayerPos.x;

    mOffsetX -= deltaX / mGap;

    float width = (float)mActualScene->GetWindowWidth();
    while (mOffsetX >= width)  mOffsetX -= width;
    while (mOffsetX < 0.f)    mOffsetX += width;

    mTransformable->setPosition(mOffsetX, mTransformable->getPosition().y);

    mPreviousPlayerPos = currentPos;
}

void Parallaxe::OnDestroy()
{
}
