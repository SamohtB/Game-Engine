#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

private:
    PhysicsCommon* physicsCommon = nullptr;
    PhysicsWorld* physicsWorld = nullptr;

};

