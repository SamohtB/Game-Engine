#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
    this->physicsCommon = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = Vector3(0, -9.81, 0);
    this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
    std::cout << "p6 succ" << std::endl;
}
