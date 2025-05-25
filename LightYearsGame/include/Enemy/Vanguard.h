#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& Velocity = {0.f, 50.f});
        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;
        unique<BulletShooter> mShooter;
    };
} // namespace ly
