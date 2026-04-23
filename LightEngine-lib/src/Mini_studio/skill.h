#pragma once
#include "Entity.h"

class Player;

class Skill : public Entity
{
private:

	int mana_cost = 3;
	bool unlocked = false;

public:

	int GetManaCost() { return mana_cost;}

	void Unlocking() { unlocked = true; };

};