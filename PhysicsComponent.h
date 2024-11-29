#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
    PhysicsComponent(String name, AGameObject* owner);
    ~PhysicsComponent();
    void perform(float deltaTime) override;
    RigidBody* getRigidBody();

private:
    float m_mass = 1000.0f;
    RigidBody* m_rigidbody = nullptr;
};

