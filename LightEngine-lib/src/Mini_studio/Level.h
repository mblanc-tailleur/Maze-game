#pragma once
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

class MainScene;

class Level
{
	struct ColliderDesc 
	{
		int xMin, xMax;
		int yMin, yMax;

		bool active = true;
	};

private:
	const char* mPlatformSymbols = "ABEFGHIJMNOPQTUVWXYZ&+@?!§°)]}=/*€(£$¤µa~#{[|%b";

	bool IsPlatformSymbol(char symbol) const;

	std::vector<std::string> mLevel = {};

	std::vector<std::vector<ColliderDesc>> mColliderDescs;

	void TryMergeCollider(ColliderDesc colliderDesc);
	void MergeVerticalCollider();

	int mPixelPerChar = 128;

	const char* _path;

public:
	Level(const char* path, MainScene* scene) : _path(path) 
	{
		OpenFile();
		ReadLevel(scene);
	}
	~Level() {}

	//void Update(sf::Vector2f playerPos);
	void ReadLevel(MainScene* scene);
	void OpenFile();
};

