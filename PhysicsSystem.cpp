#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "EngineTime.h"

typedef std::vector<PhysicsComponent*> ComponentList;

PhysicsSystem::PhysicsSystem()
{
    this->m_physics_common = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = Vector3(0, -9.81, 0);
    this->m_physics_world = this->m_physics_common->createPhysicsWorld(settings);
    std::cout << "p6 succ" << std::endl;
}

PhysicsSystem::~PhysicsSystem()
{
    if (this->m_physics_common) delete this->m_physics_common;
}

void PhysicsSystem::registerComponent(PhysicsComponent* physics_component)
{
    this->m_component_list.push_back(physics_component);
    this->m_component_table[physics_component->getName()] = physics_component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* physics_component)
{
    if (this->m_component_table[physics_component->getName()] != nullptr)
    {
        this->m_component_table.erase(physics_component->getName());

        int index = -1;
        for (int i = 0; i < this->m_component_list.size(); i++)
        {
            if (this->m_component_list[i] == physics_component)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            this->m_component_list.erase(this->m_component_list.begin() + index);
        }
        else
        {
            std::cout << "Component " << physics_component->getName() << " not registered in physics component" << std::endl;
        }
    }
}

void PhysicsSystem::unregisterComponentByName(String name)
{
    if (this->m_component_table[name] != nullptr)
    {
        this->m_component_table.erase(name);

        int index = -1;
        for (int i = 0; i < this->m_component_list.size(); i++)
        {
            if (this->m_component_list[i]->getName() == name)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            this->m_component_list.erase(this->m_component_list.begin() + index);
        }
        else
        {
            std::cout << "Component " << name << " not registered in physics component" << std::endl;
        }
    }
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
    if (this->m_component_table[name] != nullptr)
    {
        return this->m_component_table[name];
    }

    return nullptr;
}

ComponentList PhysicsSystem::getAllComponents()
{
    return this->m_component_list;
}

void PhysicsSystem::updateAllComponents()
{
    float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

    if (deltaTime > 0.0f)
    {
        this->m_physics_world->update(deltaTime);

        for (PhysicsComponent* physics : this->m_component_list)
        {
            physics->perform(deltaTime);
        }
    }

}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
    return this->m_physics_world;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
    return this->m_physics_common;
}
