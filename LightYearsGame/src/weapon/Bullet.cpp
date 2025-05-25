#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(World* World, Actor* actor, const std::string texturepath, float speed, float damage)
        :mOwner{actor},
        Actor{World, texturepath},
        mSpeed{speed},
        mDamage{damage}
    {
        SetTeamID(actor->GetTeamId());
    }

    void Bullet::setSpeed(float newspeed)
    {
        mSpeed = newspeed;
    }
    
    void Bullet::setDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        if(IsActorOutOfWindowBounds())
        {
            Destroy();      
        }
    }

    void Bullet::BeganPlay()
    {
        Actor::BeganPlay();
        SetEnabledPhysics(true);
    }
    
    void Bullet::Move(float deltaTIme)
    {
        SetActorLocationOffset(GetActorForwardDir() * mSpeed * deltaTIme);

    }

    void Bullet::OnActorBeginOverlap(Actor* other)
    {
        if(isOtherHostile(other))
        {
            other->ApplyDamage(GetDamage());
            Destroy();
        }
    }
} // namespace ly
