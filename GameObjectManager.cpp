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
    for (AGameObject* obj : sharedInstance->objectList)
    {
        delete obj;
    }

    objectList.clear();
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
    throw std::exception("FUNCTION UNAVAILABLE");
    return nullptr;
}

List GameObjectManager::getAllObjects()
{
    return this->objectList;
}

int GameObjectManager::activeObjects()
{
    int count = 0;

    for (AGameObject* obj : objectList)
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

    for (AGameObject* obj : objectList)
    {
        if (obj->isActive())
        {
            obj->update(deltaTime);
        }
    }
}

void GameObjectManager::renderAll(int viewport_width, int viewport_height)
{
    for (AGameObject* obj : objectList)
    {
        if (obj->isActive())
        {
            obj->draw(viewport_width, viewport_height);
        }
    }
}

void GameObjectManager::addGameObject(AGameObject* gameObject)
{
    this->objectList.push_back(gameObject);
    // add to hash table when object has name
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
    throw std::exception("FUNCTION UNAVAILABLE");
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
    throw std::exception("FUNCTION UNAVAILABLE");
}

void GameObjectManager::deleteObjectByName(String name)
{
    throw std::exception("FUNCTION UNAVAILABLE");
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


