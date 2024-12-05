#include "ActionHistory.h"
#include "EditorAction.h"
#include "StateManager.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;

ActionHistory* ActionHistory::getInstance()
{
    return sharedInstance;
}

void ActionHistory::initialize()
{
    sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
    delete sharedInstance;
}

void ActionHistory::recordAction(AGameObject* gameObject)
{
    if (StateManager::getInstance()->getMode() == StateManager::EditorMode::EDITOR)
    {
        EditorAction* editorAction = new EditorAction(gameObject);
        this->m_actions_performed.push(editorAction);

        std::cout << "Stored action " << gameObject->getName() << "\n";
    }
}

bool ActionHistory::hasRemainingUndoActions()
{
    return !this->m_actions_performed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
    return !this->m_actions_cancelled.empty();
}


EditorAction* ActionHistory::undoAction()
{
    if (StateManager::getInstance()->getMode() != StateManager::EditorMode::EDITOR)
    {
        std::cout << "Cannot perform any undo during play. \n";
        return nullptr;
    }

    if (this->hasRemainingUndoActions())
    {
        EditorAction* action = this->m_actions_performed.top();
        this->m_actions_performed.pop();
        this->m_actions_cancelled.push(action);
        return action;
    }

    else
    {
        std::cout << "No more actions remaining. \n";
        return nullptr;
    }
}

EditorAction* ActionHistory::redoAction()
{
    if (StateManager::getInstance()->getMode() != StateManager::EditorMode::EDITOR) {
        std::cout << "Cannot perform any redo during play. \n";
        return NULL;
    }

    if (this->hasRemainingRedoActions()) {
        EditorAction* action = this->m_actions_cancelled.top();
        this->m_actions_cancelled.pop();
        this->m_actions_performed.push(action);
        return action;
    }
    else {
        std::cout << "No more actions remaining. \n";
        return NULL;
    }
}

void ActionHistory::clear()
{
    while (this->hasRemainingUndoActions()) {
        EditorAction* action = this->m_actions_performed.top();
        delete action;
        this->m_actions_performed.pop();
    }

    while (this->hasRemainingRedoActions()) {
        EditorAction* action = this->m_actions_cancelled.top();
        delete action;
        this->m_actions_cancelled.pop();
    }
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
    this->clear();
}
