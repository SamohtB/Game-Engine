#pragma once
#include <string>
#include <vector>
#include "GameObjectManager.h"

class SceneReader
{
public:
    typedef std::string String;
    SceneReader(String directory);
    ~SceneReader();

    void ReadFromFile();

private:
    String directory;

    struct ObjectData {
        String objectName;
        AGameObject::PrimitiveType objectType;
        XMVECTOR position;
        XMVECTOR rotation;
        XMVECTOR scale;
    };

    std::vector<String> SplitString(const String& s, char delim);
};
