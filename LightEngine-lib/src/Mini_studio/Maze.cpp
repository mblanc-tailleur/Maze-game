#include "Maze.h"

void Cell::OnCollision(Entity* collidedWith, CollidingSide collidingSide)
{
	if (dynamic_cast<Cell*>(collidedWith))
	{
		return;
	}
}
