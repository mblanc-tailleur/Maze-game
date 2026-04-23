#include "MainScene.h"


float timeSpent = 0;
float timeNeeded = 1.8;

/*void MainScene::Spawn(ObjectType objectType, float levelX, float levelY)
{
	Entity* pEntity = CreateSprite<Entity>(128.f, 128.f, tilePath[(int)objectType].path, nullptr);
	pEntity->SetStatic(tilePath[(int)objectType].isStatic);

	if (pEntity != nullptr)
	{
		pEntity->SetRigidBody(true);
		pEntity->SetPosition(levelX, levelY, 0.f, 0.f);



			enum ObjectType
	{
		Enemy1,
		Enemy2,

		Count
	};
	}
}*/

void MainScene::SpawnCollider(float x, float y, float width, float height)
{
	/*Entity* pEntity = CreateRectangle<Entity>(width, height, sf::Color::Transparent, new AABBCollider(width, height));
	pEntity->SetPosition(x, y, 0.f, 0.f);
	pEntity->SetRigidBody(true);
	pEntity->SetStatic(true); */
}

void MainScene::GenerateRandomMaze()
{
	vector<vector<Cell*>*> vv;

	for (int i = 0; i < mazeHeight; i++)
	{
		vector<Cell*> v;

		for (int j = 0; j < mazeWidth; j++)
		{
			Cell* c;

			if ((i % 2 == 0) and (j % 2 == 0))
			{
				c = CreateRectangle<Cell>(50, 50, sf::Color::White, new AABBCollider(50, 50));
				c->SetRigidBody(false);
				c->type = 0;
			}

			else
			{
				c = CreateRectangle<Cell>(50, 50, sf::Color::Blue, new AABBCollider(50, 50));
				c->SetRigidBody(true);
				c->SetStatic(true);
				c->type = 1;
			}

			c->SetPosition(i * 50, j * 50);

			v.push_back(c);
		}

		vv.push_back(&v);
	}

	maze.grid = &vv;
}

void MainScene::OnInitialize() 
{
	GenerateRandomMaze();


	srand(time(NULL));

	//Player
	m_Player = CreateRectangle<Player>(30, 30, sf::Color::Red, new AABBCollider(30, 30));
	m_Player->SetPosition(0, 0);
	m_Player->SetSpeed(m_Player->GetMinSpeed());
	m_Player->SetRigidBody(true);

	GameManager::Get()->GetCamera()->SetFollowingEntity(m_Player);
}

void MainScene::OnEvent(const sf::Event& event)
{

	if (event.type == sf::Event::KeyPressed )
	{

	}


	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::D)
		{
			//std::cout << "d est relaché" << std::endl;
			m_Player->SetSpeed(0);
			m_Player->SetDirection(0, m_Player->GetPosition().y, 0);
		}
		
		if (event.key.code == sf::Keyboard::Q)
		{
			//std::cout << "q est relaché" << std::endl;
			m_Player->SetSpeed(0);
			m_Player->SetDirection(0, m_Player->GetPosition().y, 0);
		}

		if (event.key.code == sf::Keyboard::Z)
		{
			//std::cout << "z est relaché" << std::endl;
			m_Player->SetSpeed(0);
			m_Player->SetDirection(m_Player->GetPosition().x, 0, 0);
		}

		if (event.key.code == sf::Keyboard::S)
		{
			//std::cout << "q est relaché" << std::endl;
			m_Player->SetSpeed(0);
			m_Player->SetDirection(m_Player->GetPosition().x, 0, 0);
		}
	}
}





void MainScene::OnUpdate()
{
	

	//if (enemy1->telemetrie() <= 500 && enemy1 != nullptr) {
	//	std::cout << "detected" << std::endl;
	//	fall_attack = true;
	//	smart_attack = true;
	//}
	//else {
	//	std::cout << "lost" << std::endl;
	//}
	////std::cout << enemy1->telemetrie() << std::endl;
	//if (fall_attack) {
	//	ia->liveFall(enemy1);
	//}
	//if (smart_attack) {
	//	ia->liveShot(enemy1);
	//}

	
	// Squares moving
	/*timeSpent += GetDeltaTime();
	if (timeSpent >= timeNeeded)
	{
		timeSpent -= timeNeeded;
		timeNeeded *= 0.99;

		Square* s = CreateRectangle<Square>(50, 50, sf::Color::White, new AABBCollider(50, 50));
		s->SetPosition(10000, 10000);
		s->SetRigidBody(true);
		
		int mode = rand() % 4;

		int coor = rand() % 1800;

		bool followPlayer = false;

		if(followPlayer == false)
		{
			switch (mode)
			{
			case 0:
				s->SetPosition(-100, coor / 2);
				s->SetDirection(1, 0, 200);
				break;
			case 1:
				s->SetPosition(coor, -100);
				s->SetDirection(0, 1, 200);
				break;
			case 2:
				s->SetPosition(1900, coor / 2);
				s->SetDirection(-1, 0, 200);
				break;
			case 3:
				s->SetPosition(coor, 1000);
				s->SetDirection(0, -1, 200);
				break;
			}
		}

		else if (followPlayer == true)
		{
			switch (mode)
			{
			case 0:
				s->SetPosition(-100, coor / 2);
				s->SetDirection(1, 0, 200);
				break;
			case 1:
				s->SetPosition(coor, -100);
				s->SetDirection(0, 1, 200);
				break;
			case 2:
				s->SetPosition(1900, coor / 2);
				s->SetDirection(-1, 0, 200);
				break;
			case 3:
				s->SetPosition(coor, 1000);
				s->SetDirection(0, -1, 200);
				break;
			}
		}
	}
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		//std::cout << "d est pressé" << std::endl;
		m_Player->MoveRight(GetDeltaTime());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//std::cout << "q est pressé" << std::endl;
		m_Player->MoveLeft(GetDeltaTime());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		//std::cout << "d est pressé" << std::endl;
		m_Player->MoveUp(GetDeltaTime());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//std::cout << "q est pressé" << std::endl;
		m_Player->MoveDown(GetDeltaTime());
	}

	

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10) 
	{
		//std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
		m_Player->MoveRight(GetDeltaTime());

		/*if (m_Player->GetAttack() == true)*/
		
			m_Player->SetRight();
			m_Player->UnsetLeft();
		
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		const char* player_sprite = "../../../res/Sprites/course_1.png";
		//std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
		m_Player->MoveLeft(GetDeltaTime());
		
		/*if (m_Player->GetAttack() == true)*/
		
			m_Player->SetLeft();
			m_Player->UnsetRight();
	}

	Debug::DrawText(m_Player->GetPosition().x - 900, m_Player->GetPosition().y - 450, "FPS : " + std::to_string(GameManager::Get()->FPS), sf::Color::Yellow);

	/*std::cout << "x:" << m_Player->GetPosition().x << " y: " << m_Player->GetPosition().y << " speed : " << m_Player->GetSpeed() <<  std::endl;*/
}
