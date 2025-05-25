#include "framework/World.h"
#include "framework/Application.h"

namespace ly
{
    World::World(Application* owningApp)
        :mowningApp{owningApp},
        mBeganPlay{false},
        mActors{},
        mPendingActors{}
    {   

    }

    void World::BeginPlayInternal()
    {
        if(!mBeganPlay)
        {
            mBeganPlay = true;
            BeginPlay();
        }
    }

    void World::BeginPlay()
    {
    }

    void World::Tick(float deltaTime)
    {
    }

    void World::TickInternal(float deltaTime)
    {   
        for(shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeganPlayInternal();
        }
        mPendingActors.clear();

        for(auto iter = mActors.begin() ; iter != mActors.end() ;  )
        {
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }
            
        Tick(deltaTime);
    }

    void World::CleanCycle()
    {
        for(auto iter = mActors.begin() ; iter != mActors.end() ;  )
        {
            if(iter->get()->IsPendingDestroy()) 
            {
                iter = mActors.erase(iter);
            }
            else ++iter;
        }
    }

    void World::Render(sf::RenderWindow& Window)
    {
        for(auto& actor : mActors)
        {
            actor->Render(Window);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    { 
        return mowningApp->GetWindowSize();
    }

    World::~World(){}

} // namespace ly
