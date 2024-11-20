#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <exception>

#include "AGameObject.h"

typedef std::string String;
typedef std::vector<AGameObject*> List;
typedef std::unordered_map<String, AGameObject*> HashTable;

class GameObjectManager
{
public:
    enum PrimitiveType {
        CUBE,
        PLANE,
        SPHERE
    };

    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    AGameObject* findObjectByName(String name);
    List getAllObjects();
    int activeObjects();
    void updateAll();
    void renderAll(int viewport_width, int viewport_height, XMMATRIX view_matrix, XMMATRIX proj_matrix);
    void addGameObject(AGameObject* gameObject);
    void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
    void deleteObject(AGameObject* gameObject);
    void deleteObjectByName(String name);
    void setSelectedObject(String name);
    void setSelectedObject(AGameObject* gameObject);
    AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
    GameObjectManager(GameObjectManager const&) {}
    GameObjectManager& operator=(GameObjectManager const&) {}

    static GameObjectManager* sharedInstance;

    List objectList;
    HashTable objectTable;
};


