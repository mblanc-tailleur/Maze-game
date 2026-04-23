#include "Debug.h"
#include "enemies.h"

#pragma once

class sceneTemporaire : public Scene
{
private:
protected:


public:

	void OnInitialize();
	void OnEvent(const sf::Event& event);
	void OnUpdate();
};

