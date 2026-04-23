#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "Camera.h"

#define FIXED_DT 0.016667f

class Entity;
class GravityEntity;
class Scene;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
private:
	sf::Clock m_clock;
public :
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;
	Camera* mCamera;

	float mStartTimer = 0.f;
	float mProfilingTimer = 0.f;

	float mDeltaTime;
	float mAccumulatedDt = 0.f;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;


private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void FixedUpdate();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	sf::RenderWindow* GetWindow() const { return mpWindow; }

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);

	template<typename T>
	void LaunchScene();

	void StartTimer()
	{
		m_clock.restart();
	}

	float StopTimer()
	{
		return m_clock.getElapsedTime().asMilliseconds();
	}

public:

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	Camera* GetCamera() const 
	{ 
		int a = 1; 
		return mCamera;
	}
	sf::Font& GetFont() { return mFont; };
	void NewText(sf::Font* font);

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"