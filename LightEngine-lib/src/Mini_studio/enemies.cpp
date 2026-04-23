#include "enemies.h"
#include <cmath>
#include "AABBCollider.h"

/*facilite l'utilisation de la state machine*/
void enemies::choix(int nbr) {
	StateMachine state;
	state.change(nbr);
}

void enemies::init(enemies* enemy, Player* player) {
	pPlayer = player;
	pEnemy = enemy;
	Shooting_Cooldown = 0.6f;
	enemy->SetTag(2);
}

/*cree l'enemie*/
void enemies::createEnemy(float x, float y, int size){

	enemy_size = size;

}

/*evenement OnPlayerDetected*/
void enemies::OnPlayerDetected() {

}

/*evenement OnPlayerLost*/
void enemies::OnPlayerLost() {

}

/*evenement OnDeath*/
bool enemies::OnDeath(){
	if (m_PV <= 0) {
		return true;
	}else { 
		return false; 
	}
}

/*evenement OnHit*/ //need to be corrctly recode
bool enemies::OnHit() {
	if (true) {
		return true;
	}else {
		return false;
	}
}

/*evenement OnStateChanged*/
bool enemies::OnStateChanged() {
	StateMachine stateMch;
	if (stateMch.haveChange) {
		return true;
	}else {
		return false;
	}
}

/*bouge en ligne*/
void enemies::moveingInLigne(float x, float toX) {
	bool ismoving = false;
	positionEnemy = pEnemy->GetPosition();
	if (positionEnemy.x != toX ){ 
		GoToPosition(toX, positionEnemy.y);
	}
	if (positionEnemy.x != x){
		GoToPosition(x, positionEnemy.y);
	}
}

/*renvois un vecteur de l'entite cible*/
sf::Vector2f enemies::direction() {
	sf::Vector2f vectarget;

	positionEnemy = pEnemy->GetPosition();
	sf::Vector2f positiontarget = pPlayer->GetPosition();
	vectarget.x = positionEnemy.x - positiontarget.x;
	vectarget.y = positionEnemy.y - positiontarget.y;
	vectarget.x = vectarget.x;
	vectarget.y = vectarget.y;

	return vectarget;
}

/*attack fall*/
void enemies::AttackFall() {
	sf::Vector2f positiontarget = pPlayer->GetPosition();
	positionEnemy = pEnemy->GetPosition();
	float halfSize = enemy_size / 2.0f;

	if (positiontarget.x >= positionEnemy.x - halfSize &&
		positiontarget.x <= positionEnemy.x + halfSize)
	{
		//std::cout << "falling" << std::endl;
		//GoToPosition(positionEnemy.x, positiontarget.y, 100.0f);
		pEnemy->SetGravityStrength(1000);
	}
}

/*attack bulldozer*/
//void enemies::AttackBull() {
//	sf::Vector2f positiontarget = pPlayer->GetPosition();
//	positionEnemy = pEnemy->GetPosition();
//	if (positiontarget.x == positionEnemy.x + enemy_size / 2 || positiontarget.x == positionEnemy.x - enemy_size / 2) {
//		if (telemetrie()==(float)500)
//		GoToPosition(positiontarget.x, positionEnemy.y, 1.0f);
//	}
//}

/*attack punch*/
//void enemies::AttackPunch() {
//	sf::Vector2f positiontarget = pPlayer->GetPosition();
//	positionEnemy = pEnemy->GetPosition();
//	if (positiontarget.x == positionEnemy.x + enemy_size / 2 || positiontarget.x == positionEnemy.x - enemy_size / 2) {
//		if (telemetrie() == (float)50) {
//			/*attack close fight*/
//		}
//	}
//}

/*attack smart*/
void enemies::AttackSmart() {
	StateMachine state;
	sf::Vector2f positiontarget = pPlayer->GetPosition();
	positionEnemy = pEnemy->GetPosition();
	if (telemetrie() <= (float)800) {

		IsShooting = true;


		Projectile* proj = nullptr;

		Shooting_Cooldown -= GetDeltaTime();

		sf::Vector2f trgt = direction();
		//std::cout << Shooting_Cooldown << std::endl;
		if (Shooting_Cooldown < 0)
		{
			pEnemy->SetTag(2);
			std::cout << "pew-------------------------------------------------------------" << std::endl;
			//enemy2 = CreateSprite<enemies>(128, 128, R"(..\..\..\asset_by_tech\stamp.png)", new AABBCollider(128, 128));
			proj = GetScene()->CreateSprite<Projectile>(53, 53,R"(..\..\..\asset_by_tech\bullet.png)", new AABBCollider(53, 53));
			sf::Vector2f spawnPos = GetPosition(0.5f, 0.5f);
			proj->SetPosition(spawnPos.x, spawnPos.y, 0.5f, 0.5f);
			proj->SetOwnerTag(2);
			proj->SetProjectileSpeed(1.5f);
			proj->SetDirection(-trgt.x, -trgt.y, proj->GetProjectileSpeed());
			Shooting_Cooldown = 0.6f;
		}

	}
}
void enemies::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
    if (collidingSide == Bottom)
    {
        mYVelocity = 0.f;
    }
}

void enemies::setStun() {
	stun_time -= GetDeltaTime();
	bool stun = true;
	if (stun && stun_time > 0) {
		state->change(3);
		stun_time = 1;

	}
	else if (stun_time <= 0) {
		stun = false;
	}
	state->change(0);
}

void enemies::isHit(){
	pEnemy->Destroy();
}

float enemies::telemetrie() {
	if (!pEnemy) return 0.0f;

	sf::Vector2f delta = pEnemy->GetPosition() - pPlayer->GetPosition();
	return std::hypot(delta.x, delta.y);
}
