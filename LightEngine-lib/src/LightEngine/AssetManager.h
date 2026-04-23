#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

using namespace std;

class AssetManager
{
private:
    std::map<const char*, sf::Texture*> mTexturePaths;

    static AssetManager* Instance;

private:

    AssetManager();
    ~AssetManager();

    sf::Texture* LoadTexture(const char* path);

public:
    static AssetManager* Get() {
        if (Instance == nullptr) {
            Instance = new AssetManager;
        }

        return Instance;
    }

    sf::Texture* GetTexture(const char* path);
};
