#include "sceneTemporaire.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include "GravityEntity.h"
#include "Debug.h"
#include "CircleCollider.h"
#include "AABBCollider.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>




void sceneTemporaire::OnUpdate() {
	StateMachine stateMch;
	Player player;
	stateMch.haveChange = false;
	Entity* target = &player;
	Debug debuging;



	//if (enemy1.pEnemy != nullptr) {
	//	enemy1.size_enemy = 50;
	//	enemy1.AttackBull();
	//	/*enemy1.GoToPosition(500, 500);*/
	//	sf::Vector2f positionEn = enemy1.pEnemy->GetPosition();
	//	//debuging.DrawText(positionEn.x, positionEn.y, (std::string)(char), sf::Color::White);
	//	//Debug::DrawCircle(positionEn.x, positionEn.y, 10, sf::Color::Red);
	//	





	//}
}