#pragma once
#include "framework/Core.h"
#include "string"
#include <SFML/Graphics.hpp>

namespace ly
{
    class World;
    class Explosion
    {
    public:
        Explosion(int particleAmt = 20,
                  float lifetTimeMin = 0.2f,
                  float lifetTimeMax = 1.f,
                  float Sizemin = 1,
                  float Sizemax = 4,
                  float SpeedMin = 200,
                  float SpeedMax = 400,
                  const sf::Color& particleColor = sf::Color{255, 128, 0, 255},
                  const List<std::string> &particleImagePaths = {
                      "SpaceShooterRedux/PNG/Effects/star1.png",
                      "SpaceShooterRedux/PNG/Effects/star2.png",
                      "SpaceShooterRedux/PNG/Effects/star3.png"});

        void SpwanExplosion(World *world, const sf::Vector2f& location);

    private:
        int mParticleAmt;
        float mDuration;
        float mLifeTimeMin;
        float mLifeTimeMax;
        float mSizeMin;
        float mSizeMax;
        float mSpeedmin;
        float mSpeedmax;

        sf::Color mParticleColor;
        List<std::string> mParticleImagePaths;
    };
} // namespace ly
