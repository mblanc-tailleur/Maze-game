#pragma once
class StateMachine
{
private:

protected:
	enum state {
		/*0 = ne bouge pas, ne fait rien.*/
		Idle,
		/*1 = bouge.*/
		Moving,
		/*2 = recharge.*/
		Reload,
		/*3 = est incapable de bouger ou de faire quoi que se soit.*/
		Stun,
		/*4 = attaque de la zone metal ennemi 1.*/
		AttackFall,
		/*5 = attaque de la zone metal ennemi 2.*/
		AttackBull,
		/*6 = attaque de la zone jazz ennemi 1.*/
		AttackSmart,
		/*7 = attaque de la zone jazz ennemi 2.*/
		AttackPunch,
		/*8 = merci de specifiez le paterne grace a la rose des vents (N,S,E,W).*/
		AttackPatern,
		
		count
	};



	
	
public:
	bool haveChange = false;

	void change(int nbr);

	bool verifingState(int nbr);

	bool canIdle = true;
	bool canAttack = true;
	bool canReload = true;
	bool canMove = true;
};