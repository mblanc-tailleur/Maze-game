#pragma once

#include "Scene.h"

class Player;
class DummyEntity;

class Sound;
class Music;

class SampleScene : public Scene
{
	DummyEntity* pEntity1;
	DummyEntity* pEntity2;
	

	Player* gEntity;

	Player* pEntitySelected;

	Sound* mSound;
	Music* mMusic;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


