#pragma once
#include "GravityEntity.h"

void GravityEntity::Update()
{
	Entity::Update();

	mYVelocity += mGravityStrength * GetDeltaTime();
	mTransformable->setPosition(mTransformable->getPosition().x, mTransformable->getPosition().y + mYVelocity * GetDeltaTime());
}

void GravityEntity::Jump()
{

	mYVelocity = -mJumpStrength;
	
}