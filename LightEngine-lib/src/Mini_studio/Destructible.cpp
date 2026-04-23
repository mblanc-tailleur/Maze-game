#pragma once
#include "Destructible.h"

void Destructible::takeDamage()
{
	m_hp = 0;
	Destroy();
}
