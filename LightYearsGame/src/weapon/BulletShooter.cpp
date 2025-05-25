#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner, float coolDownTime)
        :Shooter{owner},
        mCoolDownClock{},
        mCoolDownTime{coolDownTime}
    {

    }

    bool BulletShooter::IsOnCooldown() const
    {
        if(mCoolDownClock.getElapsedTime().asSeconds() > mCoolDownTime)
        {
            return false;
        }

        return true;
    }

    void BulletShooter::ShootImpl()
    {
        mCoolDownClock.restart();
        // LOG("Shooting");
        weak<Bullet> newBullet = GetOwner()->GetWorld()->spwanActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        newBullet.lock()->SetActorRotationOffset(GetOwner()->GetActorRotation());

    }
} // namespace ly
