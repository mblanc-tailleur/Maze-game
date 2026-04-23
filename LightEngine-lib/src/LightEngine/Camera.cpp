#include "Camera.h"
#include "Entity.h"

Camera::Camera(const sf::Vector2f& size)
{
	mView = new sf::View(sf::Vector2f(size.x / 2, size.y / 2), size);
}

Camera::~Camera()
{
	delete mView;
}

void Camera::Update()
{
	if (mFollowingEntity == nullptr)
		return;

	SetPosition({ mFollowingEntity->GetPosition().x, mFollowingEntity->GetPosition().y - 200 });
}

sf::View* Camera::GetView()
{
	return mView;
}

Entity* Camera::GetFollowingEntity()
{
	return mFollowingEntity;
}

void Camera::SetPosition(const sf::Vector2f& pos)
{
	mView->setCenter(pos);
}

void Camera::Zoom(float factor)
{
	mView->zoom(factor);
}

void Camera::Resize(const sf::Vector2f& size)
{
	mView->setSize(size);
}

void Camera::IncreaseSize(const sf::Vector2f& increasingValue)
{
	mView->setSize(mView->getSize() + increasingValue);
}