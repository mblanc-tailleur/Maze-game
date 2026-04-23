#pragma once
#include <Entity.h>

class Destructible : public Entity
{
private:

	int m_hp = 1;

public:

	void takeDamage();
};
