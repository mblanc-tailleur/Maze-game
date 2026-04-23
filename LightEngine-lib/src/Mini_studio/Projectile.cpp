#include "Projectile.h"
#include <cmath>
#include <iostream>

#define M_PI 3.14159265358979323846

void Projectile::OnInitialize()
{
    SetRigidBody(false);
    SetStatic(false);
    SetSpeed(m_speed);
}

void Projectile::SetTarget(float x, float y)
{
    m_targetPos = { x, y };
    m_hasTarget = true;

    sf::Vector2f pos = GetPosition(0.5f, 0.5f);
    float dx = x - pos.x;
    float dy = y - pos.y;

    float len = std::sqrt(dx * dx + dy * dy);
    if (len > 0.f)
    {
        dx /= len;
        dy /= len;
    }

    SetDirection(dx, dy, m_speed);
    RotateTowardDirection(dx, dy);
}

void Projectile::SetDirectionAndRotate(float dx, float dy)
{
    float len = std::sqrt(dx * dx + dy * dy);
    if (len > 0.f) { dx /= len; dy /= len; }

    SetDirection(dx, dy, m_speed);
    RotateTowardDirection(dx, dy);
}

void Projectile::RotateTowardDirection(float dx, float dy)
{
    float angleRad = std::atan2(dy, dx);
    float angleDeg = angleRad * (180.f / static_cast<float>(M_PI));

    sf::Shape* shape = GetShape();
    if (shape)
    {
        shape->setOrigin(mWidth * 0.5f, mHeight * 0.5f);
        shape->setRotation(angleDeg);
    }
}

void Projectile::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
    if (!pOther->IsTag(m_ownerTag) && !dynamic_cast<Projectile*>(pOther))
    {
        Destroy();
    }
    
}

void Projectile::OnUpdate()
{
    sf::Vector2f cameraCenter = GameManager::Get()->GetCamera()->GetView()->getCenter();
    sf::Vector2f cameraSize = GameManager::Get()->GetCamera()->GetView()->getSize();

    sf::Vector2f pos = GetPosition(0.5f, 0.5f);
    /* bord gauche de la caméra*/
    float negative_camX = cameraCenter.x - cameraSize.x * 0.5f;
    /* bord droit de la caméra*/
    float positive_camX = cameraCenter.x + cameraSize.x * 0.5f;
    /* bord haut de la caméra*/
    float negative_camY = cameraCenter.y - cameraSize.y * 0.5f;
    /* bord bas de la caméra*/
    float positive_camY = cameraCenter.y + cameraSize.y * 0.5f;

    //std::cout << "negative_camX = " << negative_camX << std::endl;
    //std::cout << "positive_camX = " << positive_camX << std::endl;
    //std::cout << "negative_camY = " << negative_camY << std::endl;
    //std::cout << "positive_camY = " << positive_camY << std::endl; 
    
    //if (pos.x < negative_camX) { std::cout << "1.1 = pos.x < negative_camX = true" << std::endl; }
    //else { std::cout << "1.2 = pos.x < negative_camX = false" << std::endl; }
    //if (pos.x > positive_camX) { std::cout << "2.1 = pos.x > positive_camX = true" << std::endl; }
    //else { std::cout << "2.2 = pos.x > positive_camX = false" << std::endl; }
    //if (pos.y < negative_camY) { std::cout << "3.1 = pos.y < negative_camY = true" << std::endl; }
    //else { std::cout << "3.2 = pos.y < negative_camY = false" << std::endl; }
    //if (pos.y > positive_camY) { std::cout << "4.1 = pos.y > positive_camY = true" << std::endl; }
    //else { std::cout << "4.2 = pos.y > positive_camY = false" << std::endl; }

    //T^T personne ne sais ce qu'est "negative_camY", A L'AIDE  !!!

    //std::cout << "pos = " << pos.x << ", " << pos.y << std::endl;
    //std::cout << "cam center = " << cameraCenter.x << ", " << cameraCenter.y << std::endl;
    //std::cout << "cam size = " << cameraSize.x << ", " << cameraSize.y << std::endl;

    //std::cout << "pos: " << pos.x << ", " << pos.y << std::endl;
    //std::cout << "camX: " << negative_camX << " -> " << positive_camX << std::endl;
    //std::cout << "camY: " << negative_camY << " -> " << positive_camY << std::endl;

    //std::cout << "speed = " << m_speed << std::endl;

    if (pos.x <  negative_camX || pos.x > positive_camX || pos.y < negative_camY || pos.y > positive_camY) // à changer si besoin
    {

        // ici le projectile est detruit instantanement et le probleme est dans ce ".cpp"

        std::cout << "destroy" << std::endl;
        Destroy();
    }
}

void Projectile::OnDestroy()
{
}