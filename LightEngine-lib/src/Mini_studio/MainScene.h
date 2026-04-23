#pragma once
#include "Scene.h"
#include "Player.h"
#include "Parallaxe.h"

class Level;
#include "enemies.h"
#include "IA_Enemies.h"

class MainScene : public Scene
{
public:

private :
	Player* m_Player;

	std::vector<enemies*> mEnemies;

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

	std::vector<enemies*> GetEnnemyList() { return mEnemies; }

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;

	//void Spawn(ObjectType objectType, float levelX, float levelY);
	void SpawnCollider(float x, float y, float width, float height);

	void OnUpdate() override;
};