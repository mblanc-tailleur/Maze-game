#include "Square.h"

void Square::OnUpdate()
{
	if (GetPosition().x < -200 or GetPosition().x > 2000)
	{
		Destroy();
	}

	if (GetPosition().y < -200 or GetPosition().y > 1100)
	{
		Destroy();
	}
}
