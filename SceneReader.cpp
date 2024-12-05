#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PhysicsComponent.h"

SceneReader::SceneReader(String directory) : directory(directory)
{
}

SceneReader::~SceneReader()
{

}

void SceneReader::ReadFromFile()
{
    String fileDir = this->directory + ".wah";
    if (this->directory.find(".wah") != String::npos)
    {
        fileDir = this->directory;
    }

    std::ifstream sceneFile;
    sceneFile.open(fileDir, std::ios::in);

    int index = 0;
    String readLine;
    ObjectData data;

    /* Reset Scene */
    GameObjectManager::getInstance()->clearAllObjects();

    while (std::getline(sceneFile, readLine))
    {
        if (index == 0)
        {
            data.objectName = readLine;
            index++;
        }

        else if (index == 1)
        {
            std::vector stringSplit = SplitString(readLine, ' ');
            data.objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
            index++;
        }

        else if (index == 2)
        {
            std::vector stringSplit = SplitString(readLine, ' ');
            data.position = XMVectorSet(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]), 0.0f);
            index++;
        }

        else if (index == 3)
        {
            std::vector stringSplit = SplitString(readLine, ' ');
            data.rotation = XMVectorSet(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]), 0.0f);
            index++;
        }

        else if (index == 4)
        {
            std::vector stringSplit = SplitString(readLine, ' ');
            data.scale = XMVectorSet(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]), 0.0f);
            index++;
        }

        else if (index == 5)
        {
            index = 0;
            std::vector stringSplit = SplitString(readLine, ' ');
            data.hasRigidbody = std::stof(stringSplit[1]);

            AGameObject* object = GameObjectManager::getInstance()->createObject(data.objectType);
            object->setName(data.objectName);
            object->setPosition(data.position);
            object->setRotation(data.rotation);
            object->setScale(data.scale);

            if (data.hasRigidbody)
            {
                PhysicsComponent* physics = new PhysicsComponent(object->getName() + " Physics", object);
                object->attachComponent(physics);
            }
        }
    }
}

std::vector<String> SceneReader::SplitString(const String& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}
