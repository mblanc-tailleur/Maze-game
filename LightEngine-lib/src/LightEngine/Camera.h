#pragma once
#include <SFML/Graphics/View.hpp>

class Entity;

class Camera
{
private:
	sf::View* mView = nullptr;

	bool mFollow = false;
	Entity* mFollowingEntity = nullptr;

public:
	Camera(const sf::Vector2f& size);
	~Camera();
	void Update();

	sf::View* GetView();

	bool IsFollowing() { return mFollow; }
	Entity* GetFollowingEntity();

	void SetPosition(const sf::Vector2f& pos);
	void SetFollowingEntity(Entity* entity) { mFollowingEntity = entity; }
	void SetFollow(bool follow) { mFollow = follow; }

	void Zoom(float factor);

	void Resize(const sf::Vector2f& size);
	void IncreaseSize(const sf::Vector2f& increasingValue);
};

