#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float coolDownTime = 0.5f);
        virtual bool IsOnCooldown() const override;
    private: 
        virtual void ShootImpl() override; 
        sf::Clock mCoolDownClock;
        float mCoolDownTime;

    };
} // namespace ly
