#pragma once
#include "GravityEntity.h"
#include "projectile.h"
#include "skill.h"
#include "Sound.h"



class Player : public Entity 
{
private :

	bool IsAlive = true;

	float m_acceleration = 3000.f;
	float m_MaxSpeed = 1500.f;
	float m_MinSpeed = 1000.f;
	
	Entity* attack = nullptr;
	Sound* mAttackSound = nullptr;
	bool IsAttack = false;
	float Attack_Cooldown = 1;

	Projectile* proj = nullptr;
	Sound* mProjectileSound = nullptr;
	bool IsShooting = false;
	float Shooting_Cooldown = 0.6f;

	Skill* shockwave = nullptr;
	Sound* mShockwaveSound = nullptr;
	bool IsShockwave = false;
	float Shockwave_cooldown = 1;

	bool IsRight = true;
	bool IsLeft = false;
	
	Entity* Disc;
	const char* disc_sprite = "../../../res/hud/VINYL_FULL.png";

	Entity* LifeBar_back;
	Entity* LifeBar_top;
	Entity* LifeBar;
	const char* life_sprite = "../../../res/hud/JAUGE_VIE.png";

	Entity* ManaBar;
	const char* mana_sprite = "../../../res/hud/MANA_FULL.png";


public:

	void MoveRight(float deltatime);
	void MoveLeft(float delattime);
	void MoveUp(float deltatime);
	void MoveDown(float deltatime);

	void SetRight();
	void SetLeft();
	void UnsetRight() {IsRight = false; }
	void UnsetLeft() { IsLeft = false; }

	float GetAttackCD() { return Attack_Cooldown; }
	float GetShootCD() { return Shooting_Cooldown; }

	float GetMinSpeed() { return m_MinSpeed; }

	void OnCollision(Entity* pOther, CollidingSide collidingSide) override;

	
	void OnInitialize() override;
	void OnUpdate() override;

};