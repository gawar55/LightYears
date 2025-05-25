#pragma once
#include <box2d/b2_world.h>
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
    class PhysicsContactListener : public b2ContactListener
    {
    public:
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };


    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        float GetPhysicsScale() const { return mphysicsScale; }

        void RemoveListener(b2Body* bodyToRemove);
        void Cleanup();
    protected:
        PhysicsSystem();
    private:
        void ProcessPendingRemoveListeners();
        static unique<PhysicsSystem> physicsSystem;
        b2World mphyscisWorld;
        float mphysicsScale;
        int mVelocityIterations;
        int mPositionIterations;

        PhysicsContactListener mContactListener;

        Set<b2Body*> mPendingRemoveListeners;
    };
} // namespace ly

