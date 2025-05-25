#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/Application.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"
namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& TexturePath)
        :mOwningWorld{owningWorld},
        mHasBeganPlay{false},
        mSprite{},
        mTexture{},
        mPhysicBody{nullptr},
        mPhysicsEnabled{false},
        mTeamID{GetNeutralTeamId()}
    {
        setTexture(TexturePath);
    }

    Actor::~Actor()
    {
        // LOG("Actor Destroyed"); 
    }

    void Actor::BeganPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeganPlay();
        }
    }

    void Actor::BeganPlay()
    {
        // LOG("Actor Begin play");
    }

    void Actor::TickInternal(float deltaTime)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::Tick(float deltaTime)
    {
    }

    void Actor::setTexture(const std::string& TexturePath)
    {
        AssetManager& assertManager = AssetManager::Get();

        mTexture = assertManager.LoadTexture(TexturePath);
        if(!mTexture) return;

        mSprite.setTexture(*mTexture);
        int textureWidth = mTexture->getSize().x;  
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
        CentrePivot();
    }

    void Actor::OnActorBeginOverlap(Actor* other)
    {

        // LOG("Overlaped");
    }

    void Actor::OnActorEndOverlap(Actor* other)
    {
        // LOG("overlapped end");
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if(IsPendingDestroy())
            return;
        window.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLoc)
    {
        mSprite.setPosition(newLoc);
        UpdatePhysicsBodyTransfrom();

    }

    void Actor::SetActorRotation(float newRot)
    {
        mSprite.setRotation(newRot);
        UpdatePhysicsBodyTransfrom();
    }

    void Actor::SetActorLocationOffset(const sf::Vector2f& offset)
    {   
        SetActorLocation(GetActorLocation() + offset);
    }
    
    void Actor::SetActorRotationOffset(float offset)
    {
        SetActorRotation(GetActorRotation() + offset);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDir() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::Vector2f Actor::GetActorRightdDir() const
    {
        return RotationToVector(GetActorRotation() + 90.f);
    }

    void Actor::CentrePivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
    }

    sf::Vector2u Actor::GetWindowSize() const
    { 
        return mOwningWorld->GetWindowSize();
    }
    
    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    bool Actor::IsActorOutOfWindowBounds(float allowance) const
    {
        float windowWeight = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float width = GetActorGlobalBounds().width;
        float height = GetActorGlobalBounds().height;

        sf::Vector2f actorPos = GetActorLocation();

        if(actorPos.x < -width - allowance) return true;
        if(actorPos.x > windowWeight + width + allowance) return true;
        if(actorPos.y < -height - allowance) return true;
        if(actorPos.y > windowHeight + height + allowance) return true;

        return false;
    }

    void Actor::InitiallizePhysics()
    {
        if(!mPhysicBody)
        {
            mPhysicBody = PhysicsSystem::Get().AddListener(this);
        }
    }   

    void Actor::UnIntializePhysics()
    {
        if(mPhysicBody)
        {
            PhysicsSystem::Get().RemoveListener(mPhysicBody);
            mPhysicBody = nullptr;
        }
    }

    void Actor::UpdatePhysicsBodyTransfrom()
    {
        if(mPhysicBody)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale};
            float rotation = DegreesToRadians(GetActorRotation());

            mPhysicBody->SetTransform(pos, rotation);    
        }
    }

    void Actor::SetEnabledPhysics(bool enable)
    {
        mPhysicsEnabled = enable;
        if(mPhysicsEnabled)
        {
            InitiallizePhysics();
        }else
        {
            UnIntializePhysics();
        }
    }

    void Actor::Destroy()
    {
        UnIntializePhysics();
        Object::Destroy();
    }

    bool Actor::isOtherHostile(Actor* other) const
    {
        if(other == nullptr) return false;

        if(GetTeamId() == GetNeutralTeamId() && other->GetTeamId() == GetNeutralTeamId()) // changed || with &&
        {
            return false;
        }

        return GetTeamId() != other->GetTeamId();
    }

    void Actor::ApplyDamage(float amt)
    {

    }
}