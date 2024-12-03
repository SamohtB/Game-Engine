#include "GameObjectManager.h"
#include "EngineTime.h"

#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "MeshObject.h"

typedef std::string String;
typedef std::vector<AGameObject*> List;
typedef std::unordered_map<String, AGameObject*> HashTable;

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    try
    {
        sharedInstance = new GameObjectManager();
    }
    catch (...)
    {
        throw std::exception("GameObjectManager not created successfully");
    }
}

void GameObjectManager::destroy()
{
    delete sharedInstance;
}

GameObjectManager::GameObjectManager()
{
    m_name_registry = new NameRegistry();
}

GameObjectManager::~GameObjectManager()
{
    for (AGameObject* obj : sharedInstance->m_object_list)
    {
        delete obj;
    }

    m_object_list.clear();
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
    if (this->m_object_table[name] != nullptr)
    {
        return this->m_object_table[name];
    }

    return nullptr;
}

List GameObjectManager::getAllObjects()
{
    return this->m_object_list;
}

int GameObjectManager::activeObjects()
{
    int count = 0;

    for (AGameObject* obj : m_object_list)
    {
        if (obj->isActive())
        {
            count++;
        }
    }

    return count;
}

void GameObjectManager::updateAll()
{
    float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

    for (AGameObject* obj : m_object_list)
    {
        if (obj->isActive())
        {
            obj->update(deltaTime);
        }
    }
}

void GameObjectManager::renderAll(int viewport_width, int viewport_height)
{
    for (AGameObject* obj : m_object_list)
    {
        if (obj->isActive())
        {
            obj->draw(viewport_width, viewport_height);
        }
    }
}

void GameObjectManager::addGameObject(AGameObject* game_object)
{
    this->m_object_list.push_back(game_object);
    this->m_object_table[game_object->getName()] = game_object;
}

AGameObject* GameObjectManager::createObject(AGameObject::PrimitiveType type)
{
    AGameObject* spawned_object = nullptr;
    String unique_name;

    // Generate a unique name based on the object type
    switch (type)
    {
    case AGameObject::CUBE:
        unique_name = m_name_registry->getUniqueName("Cube");
        spawned_object = new Cube(unique_name);
        break;

    case AGameObject::PLANE:
        unique_name = m_name_registry->getUniqueName("Plane");
        spawned_object = new Plane(unique_name);
        break;

    case AGameObject::SPHERE:
        unique_name = m_name_registry->getUniqueName("Sphere");
        spawned_object = new Sphere(unique_name);
        break;

    case AGameObject::CYLINDER:
        unique_name = m_name_registry->getUniqueName("Cylinder");
        spawned_object = new Cylinder(unique_name);
        break;

    case AGameObject::MESH:
        unique_name = m_name_registry->getUniqueName("Mesh");
        spawned_object = new MeshObject(unique_name);
        break;

    default:
        std::cout << "INVALID OBJECT TYPE" << std::endl;
        return nullptr;
    }

    if (spawned_object != nullptr)
    {
        std::cout << "Spawned " << unique_name << std::endl;
        this->addGameObject(spawned_object);
    }

    return spawned_object;

}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
    if (this->m_object_table[game_object->getName()] != nullptr)
    {
        this->m_object_table.erase(game_object->getName());
        m_name_registry->releaseName(game_object->getName());

        int index = -1;
        for (int i = 0; i < this->m_object_list.size(); i++)
        {
            if (this->m_object_list[i] == game_object)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            this->m_object_list.erase(this->m_object_list.begin() + index);
        }
        else
        {
            std::cout << "Component " << game_object->getName() << " not registered in physics component" << std::endl;
        }
    }
}

void GameObjectManager::deleteObjectByName(String name)
{
    if (m_object_table[name] != nullptr)
    {
        AGameObject* game_object = m_object_table[name];
        deleteObject(game_object);
    }
}

void GameObjectManager::setSelectedObject(String name)
{
    this->m_selected_object = this->m_object_table[name];
}

void GameObjectManager::setSelectedObject(AGameObject* game_object)
{
    this->m_selected_object = game_object;
}

AGameObject* GameObjectManager::getSelectedObject()
{
    return this->m_selected_object;
}


