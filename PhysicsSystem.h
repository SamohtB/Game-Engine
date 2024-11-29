#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent;

class PhysicsSystem
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
    typedef std::vector<PhysicsComponent*> ComponentList;

    PhysicsSystem();
    ~PhysicsSystem();

    void registerComponent(PhysicsComponent* physics_component);
    void unregisterComponent(PhysicsComponent* physics_component);
    void unregisterComponentByName(String name);
    PhysicsComponent* findComponentByName(String name);
    ComponentList getAllComponents();

    void updateAllComponents();
    PhysicsWorld* getPhysicsWorld();
    PhysicsCommon* getPhysicsCommon();

private:
    ComponentTable m_component_table;
    ComponentList m_component_list;

    PhysicsCommon* m_physics_common = nullptr;
    PhysicsWorld* m_physics_world = nullptr;

};

