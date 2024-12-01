#include "ToolBar.h"
#include "GameObjectManager.h"

ToolBar::ToolBar() : AUIScreen("Tool Bar") {}

ToolBar::~ToolBar() {}

void ToolBar::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        /* File Menus*/
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            ImGui::MenuItem("Save");
            ImGui::EndMenu();
        }

        /* Primitive Spawners */
        if (ImGui::BeginMenu("Primitives"))
        {
            if (ImGui::MenuItem("Wood Cube")) { GameObjectManager::getInstance()->createObject(AGameObject::CUBE); }
            if (ImGui::MenuItem("Wood Plane")) { GameObjectManager::getInstance()->createObject(AGameObject::PLANE); }
            if (ImGui::MenuItem("Brick Teapot")) { GameObjectManager::getInstance()->createObject(AGameObject::MESH); }
            ImGui::EndMenu();
        }

    }

    ImGui::EndMainMenuBar();
    
}
