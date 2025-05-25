#include "Level/GameLevelOne.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "Enemy/Vanguard.h"
#include "framework/TimerManager.h"

namespace ly
{

    GameLevelOne::GameLevelOne(Application* owningApp)
        :World{owningApp}
    {
        testPlayerSpaceship = spwanActor<PlayerSpaceship>();    
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f,450.f));  
        testPlayerSpaceship.lock()->SetActorRotation(-90.f);

        weak<Vanguard> testSpaceship = spwanActor<Vanguard>();
        testSpaceship.lock()->SetActorLocation(sf::Vector2f{100.f, 50.f});
    }

    void GameLevelOne::BeginPlay()
    {
        TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 2, true);
    }

    void GameLevelOne::TimerCallback_Test()
    {
        LOG("Callback called!");
    }


} // namespace ly
