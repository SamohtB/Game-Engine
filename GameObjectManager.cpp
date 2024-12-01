#include "GameObjectManager.h"
#include "EngineTime.h"

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

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
    throw std::exception("FUNCTION UNAVAILABLE");
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
    throw std::exception("FUNCTION UNAVAILABLE");
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
    throw std::exception("FUNCTION UNAVAILABLE");
}

AGameObject* GameObjectManager::getSelectedObject()
{
    return nullptr;
}


