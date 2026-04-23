#pragma once
#include "Skill.h"
#include "enemies.h"

class enemies;

class Shockwave : public Skill
{
private:

    std::vector<enemies*> ennemies;

public:



    void ApplyEffects();

    void OnInitialize()override;
    void OnUpdate()override;
    void OnDestroy()override;

};