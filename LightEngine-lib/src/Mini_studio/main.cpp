#include "pch.h"
#include "main.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "MainScene.h"
#include "sceneTemporaire.h"

#include <cstdlib>
#include <crtdbg.h>


int main()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	srand(time(NULL));

	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1800, 900, "Scene", 60, sf::Color::Black);

	pInstance->LaunchScene<MainScene>();





	return 0;
}
