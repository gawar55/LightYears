#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
    Spaceship::Spaceship(World* owningWorld, const std::string& TexturePath)
        : Actor{owningWorld, TexturePath},
        mVelocity{},
        mHealthCom{100.f, 100.f},
        mBlinkTime{0.f},
        mBlinkDuration{0.2f},
        mBlinkColorOffset{255,0,0,255}
    {

    };

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        SetActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f& newVel)
    {
        mVelocity = newVel; 
    }

    sf::Vector2f Spaceship::GetVelocity() const {return mVelocity;}

    void  Spaceship::Shoot()
    {
        
    }

    void Spaceship::BeganPlay()
    {
        Actor::BeganPlay();
        SetEnabledPhysics(true);
        mHealthCom.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        mHealthCom.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthCom.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);

    }

    void Spaceship::Blink()
    {
        if(mBlinkTime == 0)
        {
            mBlinkTime = mBlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if(mBlinkTime > 0)
        {
            mBlinkTime -= deltaTime;
            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.0f;    

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));

        }
    }

    void Spaceship::ApplyDamage(float amt)
    {
        mHealthCom.ChangeHealth(-amt);
    }
    
    void Spaceship::OnHealthChanged(float amt,float health, float maxHealth)
    {
        // LOG("health changed by: %f, and is now: %f/%f", amt, health, maxHealth);

    }

    void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
    {
        Blink();
    }
    
    void Spaceship::Blow()
    {
        Explosion* exp = new Explosion();
        exp->SpwanExplosion(GetWorld(), GetActorLocation());
        Destroy();
        delete exp;
    }

} // namespace ly
