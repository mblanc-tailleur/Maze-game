#pragma once
#include "Entity.h"

class Player;
class MainScene;

class Parallaxe : public Entity
{
private:

    sf::Vector2f mPreviousPlayerPos;

    float mOffsetX = 0.f;
    float mGap = 3.0f;

    Player* mPlayer = nullptr;
    MainScene* mActualScene = nullptr;

    bool mInitialized = false;

public:

    void Init(MainScene* scene, float gap = 3.0f);

    void OnUpdate() override;

    void OnDestroy() override;

};
