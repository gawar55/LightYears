#include "framework/AssetManager.h"

namespace ly
{
    unique<AssetManager> AssetManager::assetManager = nullptr;
    AssetManager::AssetManager() : mRootDirectory{}
    {

    }

    void AssetManager::CleanCycle()
    {   
        for(auto itr = mLoadedTextureMap.begin() ; itr != mLoadedTextureMap.end(); )
        {
            if(itr->second.unique())
            {
                LOG("Cleaning texture: %s",itr->first.c_str());
                itr = mLoadedTextureMap.erase(itr);
            }
            else ++itr;
        }
    }
    AssetManager& AssetManager::Get()
    {
        if(!assetManager)
        {
            assetManager = unique<AssetManager>{new AssetManager};
        }
        
        return *assetManager;
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string& texturePath)
    {
        auto found = mLoadedTextureMap.find(texturePath);
        if(found != mLoadedTextureMap.end()) return found->second;

        shared<sf::Texture> newTexture{new sf::Texture};
        if(newTexture->loadFromFile(mRootDirectory + texturePath))
        {
            mLoadedTextureMap.insert({texturePath, newTexture});
            return newTexture;
        }

        return shared<sf::Texture>{nullptr};    
    }

    void AssetManager::SetAssetRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }

} // namespace ly
