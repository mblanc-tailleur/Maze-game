#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Scene.h"

class Collider;

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance = 0.f;
		bool isSet = false;
    };

public:

	enum CollidingSide 
	{
		None,
		Top,
		Bottom,
		Left,
		Right,
		Other
	};

protected:
	sf::Drawable* mDrawable = nullptr;
	sf::Transformable* mTransformable = nullptr;

	float mWidth = 0;
	float mHeight = 0;

    sf::Vector2f mDirection;
	Collider* mCollider = nullptr;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	//int mTagEnemy = 2;
	bool mRigidBody = false;
	bool mStatic = false;
	bool mActive = true;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	float GetRadius() const { return mWidth / 2.f; }
	void SetRigidBody(bool isRigidBody) { mRigidBody = isRigidBody; }
	bool IsRigidBody() const { return mRigidBody; }
	void SetStatic(bool isStatic) { mStatic = isStatic; }
	bool IsStatic() const { return mStatic; }
	void SetScale(float ratioX, float ratioY);

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape();
	sf::Sprite* GetSprite() { return (sf::Sprite*)mDrawable; }
	Collider* GetCollider() { return mCollider; }

	bool IsTag(int tag) const { return mTag == tag; }
    Entity::CollidingSide IsColliding(Entity* other) const;
	bool IsInside(float x, float y) const;
	void SetActive(bool isActive) { mActive = isActive; }
	bool IsActive() const { return mActive; }

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateRectangle(float width, float height, const sf::Color& color, Collider* collider = nullptr);

    template<typename T>
    T* CreateCircle(float radius, float outlineThickness, const sf::Color& color, Collider* collider = nullptr);

	template<typename T>
	T* CreateSprite(float width, float height, const char* texturePath, Collider* collider = nullptr);

protected:
    Entity() = default;
	~Entity() {
		delete mCollider;
		delete mDrawable;
	}

	virtual void Update();

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith, CollidingSide collidingSide) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
private:
    
	void FixedUpdate(float fixedDt);

	void Initialize(float width, float height, sf::RectangleShape* shape, const sf::Color& color, Collider* collider);
	void Initialize(float radius, sf::CircleShape* shape, const sf::Color& color, Collider* collider);
	void Initialize(float width, float height, const char* path, Collider* collider);

	virtual void Initialize() {};

	
	void Repulse(Entity* other, CollidingSide collidingSide);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"