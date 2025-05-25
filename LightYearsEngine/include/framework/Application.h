#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{   
    class World;
    class Application
    {
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
        void Run();

        template <typename worldtype>
        weak<worldtype> LoadWorld();

        sf::Vector2u GetWindowSize() const;
    
    private:
        void TickInternal(float DeltaTime);
        virtual void Tick(float DeltaTime); 

        void RenderInternal();
        virtual void Render();
    
        sf::RenderWindow mwindow;
        float mtargetFrameRate;
        sf::Clock mTickClock;
         
        shared<World> currentWorld;
        sf::Clock mCleanCycleClock;
        float mCleanCycleInterval;
    };

    template <typename worldtype>
    weak<worldtype> Application::LoadWorld()
    {
        shared<worldtype> newWorld{new worldtype(this)};
        currentWorld = newWorld;
        return newWorld;
    }

}