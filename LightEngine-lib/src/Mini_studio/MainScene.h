#pragma once
#include "Scene.h"
#include "Player.h"
#include "Parallaxe.h"
#include "Level.h"
#include "Boss.h"
#include "AABBCollider.h"
#include "Utils.h"
#include "Debug.h"
#include <iostream>
#include <random>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Square.h"
#include "Maze.h"

class Level;

class MainScene : public Scene
{
private :
	int a = 0;

	Player* m_Player;

	Level* m_Level;

	struct SpawnDesc
	{
		const char* path;
		bool isStatic;
	};

	//SpawnDesc tilePath[(int)ObjectType::Count];
	bool MoveRight = false;

	/*true = position 1; false = position 2*/
	bool Enemove = true; 
	bool fall_attack = false;
	bool smart_attack = false;

	const char* player_sprite = "../../../res/Sprites/idle_1.png";

public :
	Player* GetPlayer() { return m_Player; }

	Maze maze;

	Entity* m_light;

	int mazeWidth = 21;
	int mazeHeight = 21;

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;

	//void Spawn(ObjectType objectType, float levelX, float levelY);
	void SpawnCollider(float x, float y, float width, float height);

	void OnUpdate() override;

	void GenerateRandomMaze();
};