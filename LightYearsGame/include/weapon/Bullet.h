#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public: 
        Bullet(World* World, Actor* actor, const std::string texturepath, float speed = 500.f, float damage = 10.f);
        void setSpeed(float newspeed);
        void setDamage(float newDamage);
        float GetDamage() const {return mDamage;}
        virtual void Tick(float deltaTime);
        virtual void BeganPlay() override;
    private: 
        virtual void OnActorBeginOverlap(Actor* other) override;
        void Move(float deltaTime);
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
} // namespace ly
