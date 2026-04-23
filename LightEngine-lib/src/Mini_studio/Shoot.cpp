#include "Shoot.h"
#include "Projectile.h"
#include "AABBCollider.h"


void Shoot::Fire(int ownerTag, sf::Vector2f facingDir)
{

    AABBCollider* collider = new AABBCollider(m_projWidth, m_projHeight);

    proj = CreateSprite<Projectile>(m_projWidth, m_projHeight, m_texturePath, collider);

    proj->SetDamage(m_damage);
    proj->SetProjectileSpeed(m_projectileSpeed);
    proj->SetOwnerTag(ownerTag);

    sf::Vector2f spawnPos = GetPosition(0.5f, 0.5f);
    proj->SetPosition(spawnPos.x, spawnPos.y, 0.5f, 0.5f);

    proj->SetDirectionAndRotate(facingDir.x, facingDir.y);

}

void Shoot::OnInitialize()
{

}

void Shoot::OnUpdate()
{
    
}

void Shoot::OnDestroy()
{
}