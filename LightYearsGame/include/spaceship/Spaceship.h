#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    class Spaceship : public Actor
    {
    public:
        Spaceship(World* owningWorld, const std::string& TexturePath = "");
        void Tick(float deltaTime) override;
        void SetVelocity(const sf::Vector2f& newVel);
        
        sf::Vector2f GetVelocity() const;
        virtual void Shoot();

        virtual void BeganPlay() override;
        virtual void ApplyDamage(float amt) override;

    private:    
        virtual void OnHealthChanged(float amt, float health, float maxHealth);
        virtual void OnTakenDamage(float amt, float health, float maxHealth);    
        virtual void Blow();
        sf::Vector2f mVelocity;
        HealthComponent mHealthCom;
        void Blink();
        void UpdateBlink(float deltaTime);
        float mBlinkTime;
        float mBlinkDuration;
        sf::Color mBlinkColorOffset;
    };
} // namespace ly
