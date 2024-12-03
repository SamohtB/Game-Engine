#include "SceneWriter.h"
#include <iostream>
#include <fstream>

#include "GameObjectManager.h"

SceneWriter::SceneWriter(String directory) : directory(directory)
{

}

SceneWriter::~SceneWriter()
{

}

void SceneWriter::WriteToFile()
{
    String fileDir = this->directory + ".wah";

    if (this->directory.find(".wah") != String::npos)
    {
        fileDir = this->directory;
    }

    std::ofstream sceneFile;
    sceneFile.open(fileDir, std::ios::out);

    std::cout << "Selected filename " << fileDir << "\n";

    GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

    for (int i = 0; i < allObjects.size(); i++)
    {
        sceneFile << allObjects[i]->getName() << std::endl;
        XMVECTOR position = allObjects[i]->getLocalPosition();
        XMVECTOR rotation = allObjects[i]->getLocalRotation();
        XMVECTOR scale = allObjects[i]->getLocalScale();


        sceneFile << "Type: " << allObjects[i]->getObjectType() << std::endl;
        sceneFile << "Position: " << XMVectorGetX(position) << " " << XMVectorGetY(position) << " " << XMVectorGetZ(position) << std::endl;
        sceneFile << "Rotation: " << XMVectorGetX(rotation) << " " << XMVectorGetY(rotation) << " " << XMVectorGetZ(rotation) << std::endl;
        sceneFile << "Scale: " << XMVectorGetX(scale) << " " << XMVectorGetY(scale) << " " << XMVectorGetZ(scale) << std::endl;
    }
    sceneFile.close();
}
