#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager()
{
    for (GameObject* obj : objectList)
    {
        delete obj;
    }

    objectList.clear();
}

void GameObjectManager::registerObject(GameObject* gameObject)
{
    this->objectList.push_back(gameObject);
}

void GameObjectManager::update(float deltaTime)
{
    for (GameObject* obj : objectList)
    {
        if (obj->isActive())
        {
            obj->update(deltaTime);
        }
    }
}

void GameObjectManager::draw(int width, int height)
{
    for (GameObject* obj : objectList)
    {
        if (obj->isActive())
        {
            obj->draw(width, height);
        }
    }
}