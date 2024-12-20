#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <exception>

#include "NameRegistry.h" 
#include "AGameObject.h"

class GameObjectManager
{
public:
    typedef std::string String;
    typedef std::vector<AGameObject*> List;
    typedef std::unordered_map<String, AGameObject*> HashTable;

    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    AGameObject* findObjectByName(String name);
    List getAllObjects();
    int activeObjects();
    void updateAll();
    void renderAll(int viewport_width, int viewport_height);
    void addGameObject(AGameObject* gameObject);
    AGameObject* createObject(AGameObject::PrimitiveType type);
    void deleteObject(AGameObject* game_object);
    void deleteObjectByName(String name);
    void setSelectedObject(String name);
    void setSelectedObject(AGameObject* game_object);
    AGameObject* getSelectedObject();
    void clearAllObjects();
    void saveEditStates();
    void restoreEditStates();
    void applyEditorAction(EditorAction* action);

private:
	GameObjectManager();
	~GameObjectManager();
    GameObjectManager(GameObjectManager const&) {}
    GameObjectManager& operator=(GameObjectManager const&) {}

    static GameObjectManager* sharedInstance;

    List m_object_list;
    HashTable m_object_table;
    AGameObject* m_selected_object = nullptr;

    NameRegistry* m_name_registry = nullptr;
};


