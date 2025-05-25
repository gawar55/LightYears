#include "gameFramework/gameApplication.h"
#include "Level/GameLevelOne.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "config.h"
#include "framework/World.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        :Application{600, 900, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();

    }

} // namespace ly
