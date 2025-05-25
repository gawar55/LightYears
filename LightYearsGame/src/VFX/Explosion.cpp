#include "VFX/Explosion.h"
#include"framework/MathUtility.h"
#include "VFX/Particle.h"
#include "framework/World.h"

namespace ly
{
    Explosion::Explosion(int particleAmt, float lifetTimeMin, float lifetTimeMax, float Sizemin, float Sizemax, float SpeedMin, float SpeedMax, const sf::Color& particleColor,const List<std::string> &particleImagePaths)
        : mParticleAmt{particleAmt},
        mLifeTimeMin{lifetTimeMin},
        mLifeTimeMax{lifetTimeMax},
        mSizeMin{Sizemin},
        mSizeMax{Sizemax},
        mSpeedmin{SpeedMin},
        mSpeedmax{SpeedMax},
        mParticleColor{particleColor},
        mParticleImagePaths{particleImagePaths}
    {

    }

    void Explosion::SpwanExplosion(World* World, const sf::Vector2f& location)
    {
        if(!World) return;
        for(int i=0; i<mParticleAmt; ++i)
        {
            std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
            weak<Particle> newParticle = World->spwanActor<Particle>(particleImagePath);

            newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
            newParticle.lock()->RandomVelocity(mSpeedmin, mSpeedmax);
            newParticle.lock()->GetSprite().setColor(mParticleColor);
        }
    }

} // namespace ly
