#include "IA_Enemies.h"

//void IA::liveBull(enemies* pEnemy) {
//
//	StateMachine state;
//	sf::Vector2f positionEnemy = pEnemy-> GetPosition();
//	float distence = pEnemy->telemetrie();
//	if (distence <= 500 && state.canAttack && state.canMove) {
//		pEnemy->AttackBull();
//		state.change(5);
//	}
//	else {
//		pEnemy->moveingInLigne(0,100);
//		state.change(1);
//	}
//}

void IA::liveFall(enemies* pEnemy) {

	pEnemy->AttackFall();
	//std::cout << "fall attaque" << std::endl;
}

//void IA::livePunch(enemies* pEnemy) {
//
//	StateMachine state;
//	sf::Vector2f positionEnemy = pEnemy->GetPosition();
//	float distence = pEnemy->telemetrie();
//	if (distence <= 500 && state.canAttack) {
//		pEnemy->AttackPunch();
//
//		state.change(7);
//	}
//	else {
//		state.change(0);
//	}
//}

void IA::liveShot(enemies* pEnemy) {

	pEnemy->AttackSmart();
	//std::cout << "smart attaque" << std::endl;
}