#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
    return sharedInstance;
}

void BaseComponentSystem::initialize()
{
    sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
    delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
    return this->m_physics_system;
}

BaseComponentSystem::BaseComponentSystem()
{
    this->m_physics_system = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
    delete sharedInstance->m_physics_system;
}
