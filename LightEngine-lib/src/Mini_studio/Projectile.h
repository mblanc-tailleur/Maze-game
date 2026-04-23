#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
    int m_damage = 10;

    float m_speed = 400.f;

    sf::Vector2f m_targetPos = { 0.f, 0.f };

    bool m_hasTarget = false;

    int m_ownerTag = -1;

public:

    void SetTarget(float x, float y);

    void RotateTowardDirection(float dx, float dy);

    void SetDirectionAndRotate(float dx, float dy);

    int GetDamage() { return m_damage; };
    void SetDamage(int dmg) { m_damage = dmg; };
    float GetProjectileSpeed() { return m_speed; };
    void SetProjectileSpeed(float s) { m_speed = s; SetSpeed(s); };
    void SetOwnerTag(int tag) { m_ownerTag = tag; };
    int GetOwnerTag() { return m_ownerTag; };

    void OnCollision(Entity* pOther, CollidingSide collidingSide) override;

    void OnInitialize()override;
    void OnUpdate()override;
    void OnDestroy()override;

};