#pragma once
#include <vector>
#include "Entity.h"

using namespace std;

class Cell : public Entity
{
public:
	int type;

	// type 0 is empty cell
	// type 1 is wall
};


class Maze
{
public:
	unsigned int width;
	unsigned int height;

	vector<vector<Cell*>*>* grid;
};

