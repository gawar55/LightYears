#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"
namespace ly
{
    Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& Velocity)
        : EnemySpaceship(owningWorld, texturePath),
        mShooter{new BulletShooter(this)}

    {
        SetVelocity(Velocity);
        SetActorRotation(90.f);
    }
    
    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    } 
} // namespace ly
