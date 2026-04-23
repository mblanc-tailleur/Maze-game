#include "AssetManager.h"
#include <iostream>

using namespace std;

AssetManager* AssetManager::Instance = nullptr;

AssetManager::AssetManager() {
    Instance = nullptr;
}

AssetManager::~AssetManager() {
    for (int i = 0; i < mTexturePaths.size(); ++i) {
        delete mTexturePaths.begin()->second;
    }

    mTexturePaths.clear();

    delete Instance;
}

sf::Texture* AssetManager::LoadTexture(const char* path)
{
    sf::Texture* pTexture = new sf::Texture;

    if (pTexture->loadFromFile(path))
    {
        mTexturePaths[path] = pTexture;

        return pTexture;
    }

    std::cout << "Couldn't load texture." << std::endl;
}

sf::Texture* AssetManager::GetTexture(const char* path)
{
    auto it = mTexturePaths.find(path);

    if (it == mTexturePaths.end())
        return LoadTexture(path);

    return it->second;
}