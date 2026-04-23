#pragma once
#include "Skill.h"

class Projectile;

class Shoot : public Skill
{
private:

    float m_projWidth = 20.f;
    float m_projHeight = 10.f;

    const char* m_texturePath = "../../../res/Sprites/projectile.png";// à remplacer par le bon path

    int m_damage = 10;

    float m_projectileSpeed = 400.f;

    Projectile* proj;

public:

    int GetDamage() { return m_damage; };
    void SetDamage(int dmg) { m_damage = dmg; };
    float GetProjectileSpeed() { return m_projectileSpeed; };
    void SetProjectileSpeed(float s) { m_projectileSpeed = s; };
    void SetTexturePath(const char* p) { m_texturePath = p; };

    void Fire(int ownerTag, sf::Vector2f facingDir);

    void OnInitialize()override;
    void OnUpdate()override;
    void OnDestroy()override;
};