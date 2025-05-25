#pragma once
#include "spaceship/Spaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class BulletShooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) {mSpeed = newSpeed;}
        float GetSpeed() const {return mSpeed;}
        void ClampInputOnEdge(); 
        virtual void Shoot() override;
    private:
        void HandleInput();
        void NormalizeInput();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<BulletShooter> mShooter;
    };
} // namespace ly
