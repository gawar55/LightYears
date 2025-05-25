#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& TexturePath)
        :   Spaceship(owningWorld, TexturePath),
        mMoveInput{},
        mSpeed{200.f},
        mShooter{new BulletShooter{this,0.2f}}
    { 

    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    }

    void PlayerSpaceship::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mMoveInput.y = 1.f;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mMoveInput.x = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mMoveInput.x = 1.f;
        }
        ClampInputOnEdge(); 
        NormalizeInput();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.0f;
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(mMoveInput);
        // LOG("move input is now: %f, %f", mMoveInput.x, mMoveInput.y);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actoLoacation = GetActorLocation();
        if(actoLoacation.x < 0 && mMoveInput.x == -1.f) mMoveInput.x = 0.f;
        if(actoLoacation.x > GetWindowSize().x && mMoveInput.x == 1.f) mMoveInput.x = 0.0f;

        if(actoLoacation.y < 0 && mMoveInput.y == -1) mMoveInput.y = 0.f;
        if(actoLoacation.y > GetWindowSize().y && mMoveInput.y == 1.f) mMoveInput.y = 0.0f;

    }

    void PlayerSpaceship::Shoot()
    {
        if(mShooter)
        {
            mShooter->Shoot();
        }
    }
} // namespace ly
