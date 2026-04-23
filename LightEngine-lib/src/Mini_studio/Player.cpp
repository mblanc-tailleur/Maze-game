#include "Player.h"
#include "AABBCollider.h"
#include "Maze.h"

void Player::MoveRight(float deltatime) 
{
	//SetDirection(1, 0, 400);
	SetPosition(GetPosition().x + GetDeltaTime() * 300, GetPosition().y);
}

void Player::MoveLeft(float deltatime)
{
	//SetDirection(-1, 0, 400);
	SetPosition(GetPosition().x + GetDeltaTime() * -300, GetPosition().y);
}

void Player::MoveUp(float deltatime)
{
	//SetDirection(0, -1, 400);
	SetPosition(GetPosition().x, GetPosition().y + GetDeltaTime() * -300);
}

void Player::MoveDown(float deltatime)
{
	//SetDirection(0, 1, 400);
	SetPosition(GetPosition().x, GetPosition().y + GetDeltaTime() * 300);
}

void Player::SetRight() 
{
}

void Player::SetLeft()
{
}

void Player::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
	if (static_cast<Cell*>(pOther)->GetType() == 0)
	{
		return;
	}



	Projectile* ennemy_proj = dynamic_cast<Projectile*>(pOther);
	
	if (pOther->IsRigidBody() == true)
	{
		//pOther->Destroy();
		//Destroy();
		//exit(0);
	}


	if (ennemy_proj != nullptr && ennemy_proj->GetOwnerTag() != mTag)
	{
		//pOther->Destroy();
	}

}



void Player::OnInitialize() 
{
	SetTag(1);

	Scene* scene = GetScene();

	attack = scene->CreateRectangle<Entity>(85, 30, sf::Color::Transparent, new AABBCollider(85, 30)); 
	mAttackSound = new Sound("../../../Attack.wav");
	mProjectileSound = new Sound("../../../res/Sounds/Projectile.wav");
	mShockwaveSound = new Sound("../../../res/Sounds/Shockwave.wav");

	attack->SetPosition(GetPosition().x, GetPosition().y);
	attack->SetTag(1);

	Disc = scene->CreateSprite<Entity>(165, 165, disc_sprite, new AABBCollider(0, 0));

	LifeBar_back = scene->CreateSprite<Entity>(376, 70, "../../../res/hud/JAUGE_FOND.png", new AABBCollider(0, 0));
	LifeBar_top = scene->CreateSprite<Entity>(367, 56, "../../../res/hud/JAUGE_DESSUS.png", new AABBCollider(0, 0));
	LifeBar = scene->CreateSprite<Entity>(286, 40, life_sprite, new AABBCollider(0, 0));

	ManaBar = scene->CreateSprite<Entity>(204, 77, mana_sprite, new AABBCollider(0, 0));

}


void Player::OnUpdate() 
{
	Scene* scene = GetScene();

	if (GetPosition().x < -10)
	{
		SetPosition(-10, GetPosition().y);
	}

	if (GetPosition().x > max_X)
	{
		SetPosition(max_X, GetPosition().y);
	}

	if (GetPosition().y < -10)
	{
		SetPosition(GetPosition().x, -10);
	}

	if (GetPosition().y > max_Y)
	{
		SetPosition(GetPosition().x, max_Y);
	}


	Attack_Cooldown -= GetDeltaTime();
	
	if (attack != nullptr && Attack_Cooldown < 0) 
	{
		IsAttack = false;
		attack->SetPosition(GetPosition().x, GetPosition().y);

	}

	if (IsAttack == true && Attack_Cooldown > 0) 
	{
		
		if (IsRight) 
		{
			attack->SetPosition(GetPosition().x + 115, GetPosition().y);
			
		}
		if (IsLeft)
		{
			attack->SetPosition(GetPosition().x - 115, GetPosition().y);
			
		}
	}

	Shooting_Cooldown -= GetDeltaTime();

	if (Shooting_Cooldown < 0.f)
	{
		IsShooting = false;
		Shooting_Cooldown = 0.f;

	}

	Shockwave_cooldown -= GetDeltaTime();

	if (Shockwave_cooldown <= 0)
	{
		IsShockwave = false;
		if (shockwave != nullptr) 
		{
			shockwave->Destroy();
			shockwave = nullptr;
		}		
	}
	if (Shockwave_cooldown > 0 && IsShockwave && shockwave != nullptr)
	{
		shockwave->SetPosition(GetPosition().x, GetPosition().y);
	}

	sf::Vector2f cameraCenter = GameManager::Get()->GetCamera()->GetView()->getCenter();

	Disc->SetPosition(cameraCenter.x - 1140, cameraCenter.y - 570);
	LifeBar_back->SetPosition(Disc->GetPosition().x + 70, Disc->GetPosition().y - 70,0,0);
	LifeBar_top->SetPosition(Disc->GetPosition().x + 70, Disc->GetPosition().y - 70, 0, 0);
	LifeBar->SetPosition(Disc->GetPosition().x + 133, Disc->GetPosition().y - 62, 0, 0);
	ManaBar->SetPosition(Disc->GetPosition().x + 85, Disc->GetPosition().y - 5, 0, 0);


}