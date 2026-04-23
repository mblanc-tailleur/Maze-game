#include "Shockwave.h"
#include "Scene.h"
#include "MainScene.h"


//#include "ennemi.h" à compléter avec le bon nom de fichier


void Shockwave::OnInitialize()
{
    SetRigidBody(false);
    SetStatic(true);

    ApplyEffects();

}

void Shockwave::ApplyEffects()
{
    MainScene scene;

    sf::Vector2f origin = GetPosition(0.5f, 0.5f);

      
    ennemies = scene.GetEnnemyList(); //à remplacer avec le bon nom de fonction

    for (enemies* ennemy : ennemies)
    {
        if (ennemy == nullptr || ennemy->ToDestroy()) 
            continue;

        sf::Vector2f toEnemy = ennemy->GetPosition(0.5f, 0.5f) - origin;
        float sqDist = toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y;




    }
}

void Shockwave::OnUpdate()
{
}

void Shockwave::OnDestroy()
{
}