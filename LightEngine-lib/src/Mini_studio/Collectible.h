#pragma once
#include "Entity.h"
#include "AABBCollider.h"
#
class Collectible : public Entity
{
	bool IsEquipped = false;
	bool CanBeEquipped = false;

	void OnCollision(Entity* other, CollidingSide collidingSide) override;
	void Update();
	void GetNotify();
};

