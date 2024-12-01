#include "GameObjectManager.h"
#include "EngineTime.h"

#include "Cube.h"
#include "Plane.h"
#include "MeshObject.h"

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

GameObjectManager::GameObjectManager() {}

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

    switch (type)
    {
    case AGameObject::CUBE:
        spawned_object = static_cast<AGameObject*>(new Cube("Cube_" + std::to_string(this->m_cube_count)));
        this->m_cube_count++;
        break;

    case AGameObject::PLANE:
        /*spawned_object = static_cast<AGameObject*>(new Plane("Plane_" + std::to_string(this->m_cube_count), 0.15f));
        this->m_mesh_count++;*/
        break;

    case AGameObject::MESH:
        spawned_object = static_cast<AGameObject*>(new MeshObject("Teapot_" + std::to_string(this->m_mesh_count)));
        this->m_mesh_count++;
        break;

    default:
        std::cout << "INVALID OBJECT TYPE" << std::endl;
        break;
    }

    if (spawned_object != nullptr)
    {
        this->addGameObject(spawned_object);
        std::cout << "Spawned " << spawned_object->getObjectType() << std::endl;
        return spawned_object;
    }
    

}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
    if (this->m_object_table[game_object->getName()] != nullptr)
    {
        this->m_object_table.erase(game_object->getName());

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
    if (this->m_object_table[name] != nullptr)
    {
        this->m_object_table.erase(name);

        int index = -1;
        for (int i = 0; i < this->m_object_list.size(); i++)
        {
            if (this->m_object_list[i]->getName() == name)
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
            std::cout << "Component " << name << " not registered in physics component" << std::endl;
        }
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


