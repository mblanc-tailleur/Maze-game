#include "Player.h"

void Player::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
	if (collidingSide == Bottom)
		mYVelocity = 0.f;
}
