#pragma once
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly
{
    class AssetManager
    {
    public:
        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& texturePath);

        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);

    protected:
        AssetManager();
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        std::string mRootDirectory;
    };
}