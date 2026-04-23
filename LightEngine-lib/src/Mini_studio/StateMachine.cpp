#include "StateMachine.h"

void StateMachine::change(int nbr) {

	if (nbr == 0) {
		state(Idle);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can realod
		canReload = true;
		//can move
		canMove = true;
	}
	else if (nbr == 1) {
		state(Moving);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can realod
		canReload = true;
		//can move
		canMove = true;
	}
	else if (nbr == 2) {
		state(Reload);
		//can idle
		canIdle = true;
		//can not attack
		canAttack = false;
		//can not realod
		canReload = false;
		//can move
		canMove = true;
	}
	else if (nbr == 3) {
		state(Stun);
		//can not idle
		canIdle = false;
		//can not attack
		canAttack = false;
		//can not realod
		canReload = false;
		//can not move
		canMove = false;
	}
	else if (nbr == 4) {
		state(AttackFall);
		//can not idle
		canIdle = false;
		//can attack
		canAttack = true;
		//can not realod
		canReload = false;
		//can not move
		canMove = false;
	}
	else if (nbr == 5) {
		state(AttackBull);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can not realod
		canReload = false;
		//can move
		canMove = true;
	}
	else if (nbr == 6) {
		state(AttackSmart);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can realod
		canReload = true;
		//can move
		canMove = true;
	}
	else if (nbr == 7) {
		state(AttackPunch);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can realod
		canReload = true;
		//can not move
		canMove = false;
	}
	else if (nbr == 8) {
		state(AttackPatern);
		//can idle
		canIdle = true;
		//can attack
		canAttack = true;
		//can realod
		canReload = true;
		//can move
		canMove = true;
	}

	haveChange = true;
}

bool StateMachine::verifingState(int nbr) {
	return true;
}
