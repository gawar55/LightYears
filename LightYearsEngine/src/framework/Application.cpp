#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"


namespace ly
{   
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style) 
        : mwindow(sf::VideoMode(windowWidth,windowHeight), title,style),
            mtargetFrameRate{60.0f} , mTickClock{},
            currentWorld{nullptr},
            mCleanCycleClock{},
            mCleanCycleInterval{2.f}
    {
        
    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.0f;
        float TargetDelataTime = 1.0f / mtargetFrameRate;
        while(mwindow.isOpen())
        {
            sf::Event WindowEvent;
            while(mwindow.pollEvent(WindowEvent))
            { 
                if(WindowEvent.type == sf::Event::EventType::Closed)
                {
                    mwindow.close();
                }
            }
            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while(accumulatedTime > TargetDelataTime)
            {
                accumulatedTime -= TargetDelataTime;
                TickInternal(TargetDelataTime);
                RenderInternal();
            }
        }
    }
    
    void Application::TickInternal(float DeltaTime)
    {
        Tick(DeltaTime);
        
        if(currentWorld)
        {
            currentWorld->BeginPlayInternal();
            currentWorld->TickInternal(DeltaTime);
        }

        TimerManager::Get().UpdateTimer(DeltaTime);

        PhysicsSystem::Get().Step(DeltaTime);
        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if(currentWorld)
            {
                currentWorld->CleanCycle();
            }
        }
    }
    
    void Application::RenderInternal()
    {
        mwindow.clear();

        Render();
        
        mwindow.display();
    }

    void Application::Render()
    {
        if(currentWorld)
        {
            currentWorld->Render(mwindow);
        }
       
    }

    void Application::Tick(float DeltaTime)
    {

    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return mwindow.getSize();
    }
}

