#include "Attack.h"
#include "../LightEngine/Entity.h"
#include "Shoot.h"
#include "CircleCollider.h"
#include "Player.h"
#include "Projectile.h"


#include <iostream>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Thread.hpp>
#include "StateMachine.h"

#pragma once
class enemies : public GravityEntity
{
private:

	
	float stun_time = 1.f;
protected:
	int m_PV{ 5 };


	

public:
	int enemy_size{ 100 };
	enemies* pEnemy = nullptr;
	Player* pPlayer = nullptr;
	float size_enemy = 0;
	StateMachine* state = nullptr;
	sf::Vector2f positionEnemy;

	void choix(int nbr);

	void init(enemies* enemy, Player* player);

	/*cree des ennemis*/
	void createEnemy(float x, float y, int size);

	void OnPlayerDetected();

	void OnPlayerLost();

	bool OnDeath();

	bool OnHit();

	bool OnStateChanged();

	void moveingInLigne(float x, float toX);

	/*renvois un vecteur de l'entite cible*/
	sf::Vector2f direction();

	/*attaque de l'enemies*/
	void AttackFall();

	//void AttackBull();

	//void AttackPunch();

	void AttackSmart();

	void OnCollision(Entity* pOther, CollidingSide collidingSide) override;

	void setStun();

	void isHit();

	float telemetrie();

	sf::Transformable* GetTransformable() { return mTransformable ; }

	bool IsShooting = false;
	float Shooting_Cooldown = 0.0f;
};
