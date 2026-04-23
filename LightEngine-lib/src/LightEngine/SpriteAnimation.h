#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <vector>

using namespace std;

class SpriteAnimation
{
    public:
        sf::Texture* Textures;
        vector<int> Delays;
        bool isLoop;

        int frameWidth;
        int frameHeight;
        int line;
        int column;
};