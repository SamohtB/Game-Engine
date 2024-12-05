#include "StateManager.h"
#include "GameObjectManager.h"

StateManager* StateManager::sharedInstance = nullptr;

StateManager* StateManager::getInstance()
{
    return sharedInstance;
}

void StateManager::initialize()
{
    sharedInstance = new StateManager();
}

void StateManager::destroy()
{
    delete sharedInstance;
}

void StateManager::setMode(StateManager::EditorMode mode)
{
    this->m_editor_mode = mode;

    if (this->m_editor_mode == EditorMode::PLAY)
    {
        GameObjectManager::getInstance()->saveEditStates();
    }
    else if (this->m_editor_mode == EditorMode::EDITOR)
    {
        GameObjectManager::getInstance()->restoreEditStates();
    }
}

void StateManager::startFrameStep()
{
    this->m_frame_stepping = true;
}

void StateManager::endFrameStep()
{
    this->m_frame_stepping = false;
}

bool StateManager::insideFrameStep()
{
    return this->m_frame_stepping;
}

StateManager::EditorMode StateManager::getMode()
{
    return this->m_editor_mode;
}

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}
