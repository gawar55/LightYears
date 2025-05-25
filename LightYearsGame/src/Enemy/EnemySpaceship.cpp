#include "Enemy/EnemySpaceship.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
        : Spaceship{owningWorld, texturePath},
        mCollisionDamage{collisionDamage}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor* other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if(isOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }

    void EnemySpaceship::Tick(float deltaTIme)
    {
        Spaceship::Tick(deltaTIme);
        if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
            Destroy();
    }

} // namespace ly
