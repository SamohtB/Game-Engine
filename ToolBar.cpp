#include "ToolBar.h"
#include "GameObjectManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"
#include "ActionHistory.h"
#include "StateManager.h"

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
            if (ImGui::MenuItem("Capsule")) { GameObjectManager::getInstance()->createObject(AGameObject::CAPSULE); }
            if (ImGui::MenuItem("Teapot")) { GameObjectManager::getInstance()->createObject(AGameObject::MESH); }
            ImGui::EndMenu();
        }

        float window_width = ImGui::GetWindowSize().x;
        float text_width = ImGui::CalcTextSize("Play").x + ImGui::CalcTextSize("Pause").x + ImGui::CalcTextSize("Stop").x + ImGui::CalcTextSize("Resume").x;
        float available_width = window_width - text_width;

        ImGui::SameLine(available_width / 2);

        if (StateManager::getInstance()->getMode() == StateManager::EDITOR)
        {
            if (ImGui::Button("Play"))
            {
                StateManager::getInstance()->setMode(StateManager::PLAY);
            }
        }
        else if (StateManager::getInstance()->getMode() != StateManager::EDITOR)
        {
            if (ImGui::Button("Stop"))
            {
                StateManager::getInstance()->setMode(StateManager::EDITOR);
            }
        }


        if (StateManager::getInstance()->getMode() == StateManager::PLAY)
        {
            if (ImGui::Button("Pause"))
            {
                StateManager::getInstance()->setMode(StateManager::PAUSED);
            }
        }
        else if (StateManager::getInstance()->getMode() == StateManager::PAUSED)
        {
            if (ImGui::Button("Resume"))
            {
                StateManager::getInstance()->setMode(StateManager::PLAY);
            }
        }

        if (StateManager::getInstance()->getMode() == StateManager::EDITOR)
        {
            ImGui::SameLine(0, window_width - available_width / 2 - text_width);

            if (ImGui::Button("Undo"))
            {
                if (ActionHistory::getInstance()->hasRemainingUndoActions())
                {
                    GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction());
                }

            }

            if (ImGui::Button("Redo"))
            {
                if (ActionHistory::getInstance()->hasRemainingRedoActions())
                {
                    GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction());
                }
            }
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
