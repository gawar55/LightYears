#pragma once
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{   
    class Actor;
    class Application;
    class World : public Object
    {
    public:
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual ~World();
        
        template<typename ActorType, typename... Args>
        weak<ActorType> spwanActor(Args... args);

        void Render(sf::RenderWindow& Window);

        sf::Vector2u GetWindowSize() const;

        void CleanCycle();
    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        Application* mowningApp;
        bool mBeganPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
    };

    template<typename ActorType, typename... Args>
    weak<ActorType> World::spwanActor(Args... args)
    {
        shared<ActorType> newActor{new ActorType(this, args...)};
        mPendingActors.push_back(newActor);
        return newActor;
    }
} // namespace ly
