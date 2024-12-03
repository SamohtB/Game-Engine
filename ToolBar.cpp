#include "ToolBar.h"
#include "GameObjectManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"

ToolBar::ToolBar() : AUIScreen("Tool Bar") {}

ToolBar::~ToolBar() {}

void ToolBar::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        /* File Menus*/
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Scene"))
            {
                this->m_save_window = true;
            }

            if (ImGui::MenuItem("Load Scene"))
            {
                this->m_load_window = true;
            }

            ImGui::EndMenu();
        }

        if (this->m_save_window)
        {
            drawSaveSceneWindow();
        }

        if (this->m_load_window)
        {
            drawLoadSceneWindow();
        }

        /* Primitive Spawners */
        if (ImGui::BeginMenu("Primitives"))
        {
            if (ImGui::MenuItem("Cube")) { GameObjectManager::getInstance()->createObject(AGameObject::CUBE); }
            if (ImGui::MenuItem("Plane")) { GameObjectManager::getInstance()->createObject(AGameObject::PLANE); }
            if (ImGui::MenuItem("Sphere")) { GameObjectManager::getInstance()->createObject(AGameObject::SPHERE); }
            if (ImGui::MenuItem("Cylinder")) { GameObjectManager::getInstance()->createObject(AGameObject::CYLINDER); }
            if (ImGui::MenuItem("Teapot")) { GameObjectManager::getInstance()->createObject(AGameObject::MESH); }
            ImGui::EndMenu();
        }

    }

    ImGui::EndMainMenuBar();
    
}

void ToolBar::drawLoadSceneWindow()
{
    ImGui::OpenPopup("Load Scene Window");

    if (ImGui::BeginPopupModal("Load Scene Window", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Load File Name", loadFileName, IM_ARRAYSIZE(loadFileName));

        if (ImGui::Button("Load"))
        {
            if (strlen(loadFileName) > 0)
            {
                std::string fullFileName = m_scene_directory + loadFileName;
                SceneReader screenReader(fullFileName);
                screenReader.ReadFromFile();
                ImGui::CloseCurrentPopup();
                this->m_load_window = false;
            }
            else
            {
                ImGui::Text("Please enter a file name.");
            }
        }

        if (ImGui::Button("Cancel"))
        {
            this->m_load_window = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void ToolBar::drawSaveSceneWindow()
{
    ImGui::OpenPopup("Save Scene Window");

    if (ImGui::BeginPopupModal("Save Scene Window", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Save File Name", saveFileName, IM_ARRAYSIZE(saveFileName));

        if (ImGui::Button("Save"))
        {
            if (strlen(saveFileName) > 0)
            {
                std::string fullFileName = m_scene_directory + saveFileName;
                SceneWriter screenWriter(fullFileName);
                screenWriter.WriteToFile();
                ImGui::CloseCurrentPopup();
                this->m_save_window = false;
            }
            else
            {
                ImGui::Text("Please enter a file name.");
            }
        }

        if (ImGui::Button("Cancel"))
        {
            this->m_save_window = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}
