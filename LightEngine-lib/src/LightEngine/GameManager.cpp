#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;
	mCamera = nullptr;
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mpScene;
	delete mCamera;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mCamera = new Camera(sf::Vector2f(width, height));

	mClearColor = clearColor;
}
float timer = 0.0f;

void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mpScene != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		timer += mDeltaTime;
		if (timer > 1.f)
		{
			FPS = (int)(1.f / mDeltaTime);
			timer = 0.f;
		}
			
		

		HandleInput();

		Update();
		
		Draw();
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}

		mpScene->OnEvent(event);
	}
}

void GameManager::Update()
{
	mpScene->OnUpdate();

	sf::Vector2f cameraPos = mCamera->GetView()->getCenter();
	sf::Vector2f cameraSize = mCamera->GetView()->getSize();

    //Update
    for (auto it = mEntities.begin(); it != mEntities.end(); )
    {
		Entity* entity = *it;

		/*if (entity->GetPosition(1, 0.5).x < cameraPos.x - cameraSize.x / 2 || entity->GetPosition(0, 0.5).x > cameraPos.x + cameraSize.x / 2)
			entity->SetActive(false);
		else if (entity->GetPosition(0.5, 1).y < cameraPos.y - cameraSize.y / 2 || entity->GetPosition(0.5, 0).y > cameraPos.y + cameraSize.y / 2)
			entity->SetActive(false);*/

        entity->Update();

        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }

        mEntitiesToDestroy.push_back(entity);
        it = mEntities.erase(it);
    }

	//Fixed Update
	mAccumulatedDt += mDeltaTime;
	while (mAccumulatedDt >= FIXED_DT)
	{
		FixedUpdate();
		mAccumulatedDt -= FIXED_DT;
	}

	//Camera
	if (mCamera != nullptr)
	{
		mCamera->Update();

		if (mCamera->GetView() != nullptr)
			mpWindow->setView(*mCamera->GetView());
	}

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();
}

void GameManager::FixedUpdate()
{
	int colliderCount = 0;
	// Physic update
	for (Entity* entity : mEntities)
	{
		entity->FixedUpdate(FIXED_DT);
	}

	// Collision detection

	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		it2++;

		Entity* entity = *it1;

		if (entity->IsActive() == false || entity->GetCollider() == nullptr)
			continue;

		for (it2; it2 != mEntities.end(); ++it2)
		{
			
			Entity* otherEntity = *it2;

			if (entity->IsActive() == false || otherEntity->IsActive() == false)
				continue;

			Entity::CollidingSide collidingSide = entity->IsColliding(otherEntity);

			if (collidingSide != Entity::CollidingSide::None)
			{
				if (entity->IsRigidBody() && otherEntity->IsRigidBody())
					entity->Repulse(otherEntity, collidingSide);

				entity->OnCollision(otherEntity, collidingSide);

				switch (collidingSide)
				{
				case Entity::Top:
					collidingSide = Entity::Bottom;
					break;
				case Entity::Bottom:
					collidingSide = Entity::Top;
					break;
				case Entity::Left:
					collidingSide = Entity::Right;
					break;
				case Entity::Right:
					collidingSide = Entity::Left;
				}

				otherEntity->OnCollision(entity, collidingSide);
			}
		}
	}
}

void GameManager::Draw()
{
	mpWindow->clear(mClearColor);
	
	for (Entity* entity : mEntities)
	{
		if (entity->IsActive() == false)
			continue;

		if (sf::Shape* entityShape = entity->GetShape())
		{
			mpWindow->draw(*entityShape);
		}
		else if (sf::Sprite* entitySprite = entity->GetSprite())
			mpWindow->draw(*entitySprite);
	}
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
 }