#pragma once
#include <vector>
#include "Entity.h"

using namespace std;

class Cell : public Entity
{
public:
	int X;
	int Y;

	int type;
	bool hasBeenVisited = false;


	void OnCollision(Entity* collidedWith, CollidingSide collidingSide) override;
	int GetType() const { return type; }
	// type 0 is empty cell
	// type 1 is wall
};


class Maze
{
public:
	unsigned int width;
	unsigned int height;

	vector<vector<Cell*>> grid;
};

