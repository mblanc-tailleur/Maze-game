#pragma once
#include "GravityEntity.h"

class Player :
    public GravityEntity
{
public:
    void OnCollision(Entity* pOther, CollidingSide collidingSide) override;
};

