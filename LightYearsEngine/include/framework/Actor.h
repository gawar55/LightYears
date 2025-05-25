#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

class b2Body;
namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& TexturePath = "");

        void BeganPlayInternal();
        void TickInternal(float deltaTime);

        virtual ~Actor();
        virtual void BeganPlay();
        virtual void Tick(float deltaTime); 

        void Render(sf::RenderWindow& window);
        void setTexture(const std::string& TexturePath);
        void SetActorLocation(const sf::Vector2f& newLoc);
        void SetActorRotation(float newRot);
        void SetActorLocationOffset(const sf::Vector2f& offset);
        void SetActorRotationOffset(float offset);

        sf::Vector2f GetActorLocation() const;
        float GetActorRotation() const;

        sf::Vector2f GetActorForwardDir() const;
        sf::Vector2f GetActorRightdDir() const;
        sf::FloatRect GetActorGlobalBounds() const;
        sf::Vector2u GetWindowSize() const;

        World* GetWorld() { return mOwningWorld; }
        const World* GetWorld() const { return mOwningWorld; }

        bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

        void SetEnabledPhysics(bool enable);
        void UpdatePhysicsBodyTransfrom();

        virtual void ApplyDamage(float amt);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        virtual void Destroy() override;

        static uint8 GetNeutralTeamId() { return neutralTeam;}
        uint8 GetTeamId() const { return mTeamID;}
        bool isOtherHostile(Actor* other) const;
        void SetTeamID(uint8 teamId) { mTeamID = teamId; }

        sf::Sprite& GetSprite() { return mSprite; }
        const sf::Sprite& GetSprite() const { return mSprite; }

        private:
        void InitiallizePhysics();
        void UnIntializePhysics();
        void CentrePivot();
        World* mOwningWorld;
        
        sf::Sprite mSprite; 
        shared<sf::Texture> mTexture;

        bool mHasBeganPlay;
        b2Body* mPhysicBody;

        bool mPhysicsEnabled;

        uint8 mTeamID;

        const static uint8 neutralTeam = 255;
    };
} // namespace ly
