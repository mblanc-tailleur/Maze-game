#include "Boss.h"
#include "Projectile.h"
#include "AABBCollider.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"

void Boss::OnInitialize()
{
	LaunchAtk();
	SetSpeed(mBaseSpeed);
	SetTag(3);

	mMusic = new Music("../../../res/Musics/Boss_Music.wav");
	mMusic->Play();
	mMusic->SetLoop(true);

	mHealSound = new Sound("../../../res/Sounds/heal.wav");
	mDashSound = new Sound("../../../res/Sounds/Dash_Boss.wav");
}

Projectile* pProjectile;
void Boss::OnUpdate()
{
	mWaitTimer -= GetDeltaTime();
	mInvulnerabilityTime -= GetDeltaTime();

	if (mHp <= 0)
		Destroy();

	if (mFunction != nullptr)
		mFunction();
}


void Boss::LaunchAtk()
{
	int randomAtk = rand() % 4;
	//int randomAtk = 1;

	switch (randomAtk)
	{
	case 0:
		mFunction = std::bind(&Boss::DashAtk, this);
		break;
	case 1:
		mFunction = std::bind(&Boss::ProjectileAtk, this);
		break;
	case 2:
		mFunction = std::bind(&Boss::ShockwaveAtk, this);
		break;
	case 3:
		mFunction = std::bind(&Boss::HealAtk, this);
		break;
	}

	mAtkStep = 0;
	mFunction();
}

void Boss::DashAtk() 
{
	switch (mAtkStep) 
	{
	case 0:
		// Go on the top of the screen
		GoToPosition(mCenterX, mUpperY);
		mAtkStep++;
		break;
	case 1:
		if (mTarget.isSet == false)
		{
			mWaitTimer = 0.5f;
			mAtkStep++;
		}
		break;
	case 2:
		if (mWaitTimer <= 0.f)
			mAtkStep++;
		break;
	case 3:
		// if on top of the screen go to a random side (right / left)
		if (mTarget.isSet == false)
		{
			if (rand() % 2 == 1)
				SetPosition(mLeftSideX, mLeftSideY);
			else
				SetPosition(mRightSideX, mRightSideY);
			mAtkStep++;
			mWaitTimer = 1.5f;
		}
		break;
	case 4:
		// Wait 1.5 seconds
		if (mWaitTimer <= 0.f)
		{
			mAtkStep++;

			// Dash to the other side
			SetSpeed(mAccelerationSpeed);
			mDashSound->Play();

			if (GetPosition().x == mLeftSideX)
			{
				GoToPosition(mRightSideX, mRightSideY);
			}
			else
			{
				GoToPosition(mLeftSideX, mLeftSideY);
			}
		}
		break;
	case 5:
		// Reset speed
		if (mTarget.isSet == false)
		{
			SetSpeed(mBaseSpeed);
			mAtkStep++;
			mWaitTimer = 1.5f;
		}
		break;
	case 6:
		// Wait 1.5 seconds
		if (mWaitTimer <= 0.f)
		{
			mAtkStep++;
			// Go to center of the scene
			GoToPosition(0, 0);
		}
		break;
	case 7:
		if (mTarget.isSet == false)
		{
			mAtkStep++;
			mWaitTimer = 1.f;
		}
		break;
	case 8:
		// Wait 1 second
		if (mWaitTimer <= 0.f)
			mAtkStep++;
		break;
	case 9:
		//Change Atk
		LaunchAtk();
		break;
	}
}

void Boss::ProjectileAtk()
{
	switch (mAtkStep)
	{
	case 0:
		mWaitTimer = 1.f;
		mAtkStep++;
		break;
	case 1:
		//Wait 1 second then choose a random number of projectile
		if (mWaitTimer <= 0.f)
		{
			mProjectileNb = rand() % 10 + 15;
			mAtkStep++;
		}
		break;
	case 2:
		//Shoot projectiles
		if (mWaitTimer <= 0.f)
		{
			Projectile* pProjectile = CreateSprite<Projectile>(128, 250, "../../../res/Sprites/Boss/Boss_Projectile.png", new AABBCollider(135, 240));
			pProjectile->SetOwnerTag(3);
			pProjectile->SetPosition(rand() % 2500 - 1500, -500);
			pProjectile->SetDirection(0, 1, 800);
			mWaitTimer = 0.3f;
			mProjectileNb -= 1;
		}
		
		if (mProjectileNb <= 0)
		{
			mWaitTimer = 2.5f;
			mAtkStep++;
		}
		break;
	case 3:
		//Wait
		if (mWaitTimer <= 0.f)
			mAtkStep++;
		break;
	case 4:
		//Change Atk
		LaunchAtk();
		break;
	}
}

void Boss::ShockwaveAtk()
{
	switch (mAtkStep)
	{
	case 0:
		mWaitTimer = 2.5f;
		mAtkStep++;
		break;
	case 1:
		if (mWaitTimer <= 0.f)
		{
			mAtkStep++;
		}
		else
		{
			Debug::DrawRectangle(mCenterX - 450, mCenterY - 450, 900, 900, sf::Color::Cyan); // Draw a indication for the player
		}
		break;
	case 2:
		mShockwave = CreateSprite<Entity>(900, 900, "../../../res/Sprites/Boss/Boss_Shockwave.png", new AABBCollider(900, 900));
		mShockwave->SetPosition(mCenterX, mCenterY);
		mShockwave->SetStatic(true);
		//mShockwave->SetRigidBody(true);

		mWaitTimer = 1.f;
		mAtkStep++;
		break;
	case 3:
		if (mWaitTimer <= 0.f)
		{
			mAtkStep++;
			mShockwave->Destroy();
			mShockwave = nullptr;
		}
		break;
	case 4:
		mAtkStep++;
		break;
	case 5:
		GoToPosition(mCenterX, mCenterY);
		mAtkStep++;
		break;
	case 6:
		if (mTarget.isSet == false)
		{
			mAtkStep++;
		}
		break;
	case 7:
		LaunchAtk();
		break;
	}
}

void Boss::HealAtk()
{
	switch (mAtkStep)
	{
	case 0:
		if (mHealSound != nullptr)
			mHealSound->Play();
		mHp = std::min(mHpMax, mHp + 5);
		mAtkStep++;
		//Add some things like repeat it and wait between heals
		mWaitTimer = 1.f;
		break;
	case 1:
		if (mWaitTimer <= 0.f)
			mAtkStep++;
		break;
	case 2:
		LaunchAtk();
		break;
	}
}

void Boss::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
	Projectile* collidingProjectile = dynamic_cast<Projectile*> (pOther);

	if (collidingProjectile == nullptr)
		return;

	if (collidingProjectile->GetOwnerTag() == 3) // TODO Compare if it's a projectile of the boss (for the moment the tag of the boss is 3 as shown in the condition)
		return;

	if (mInvulnerabilityTime <= 0.f)
	{
		mHp -= 1; // TODO Change with the attack of pOther
		mInvulnerabilityTime = 0.2f;
	}
}

void Boss::OnDestruction()
{
	mMusic->Stop();
	delete mMusic;
	delete mHealSound;
}
