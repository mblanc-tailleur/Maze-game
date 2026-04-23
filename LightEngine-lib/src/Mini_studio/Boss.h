#pragma once
#include "Entity.h"

#include <functional>

class Music;
class Sound;

class Boss : 
	public Entity
{
private:
	int mAtkStep = -1;

	int mHp = 25;
	int mHpMax = 25;

	Music* mMusic = nullptr;
	Sound* mHealSound = nullptr;
	Sound* mDashSound = nullptr;

	// Ces variables sont à changer selon la scène une fois qu'elle sera faite.
	float mUpperY = -720;

	float mCenterX = 0;
	float mCenterY = 0;

	float mLeftSideX = -2100;
	float mLeftSideY = 520;

	float mRightSideX = 2100;
	float mRightSideY = 520;

	float mBaseSpeed = 1200.f;
	float mAccelerationSpeed = 1500.f;

	float mWaitTimer = 0.f;
	float mInvulnerabilityTime = 0.f;

	float mProjectileNb = 0.f;

	Entity* mShockwave = nullptr;

	//

	std::function<void()> mFunction;

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pOther, CollidingSide collidingSide) override;
	void OnDestruction();

public:

	void LaunchAtk();

	void DashAtk();
	void ProjectileAtk();
	void ShockwaveAtk();
	void HealAtk();
};