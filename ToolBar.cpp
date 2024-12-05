#include "ToolBar.h"
#include "GameObjectManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"
#include "ActionHistory.h"
#include "StateManager.h"

ToolBar::ToolBar() : AUIScreen("Tool Bar")
{
    this->m_load_scene_browser = new ImGui::FileBrowser();
    this->m_load_scene_browser->SetTitle("Load Scene");
    this->m_load_scene_browser->SetTypeFilters({ ".wah" });

    this->m_save_scene_browser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
    this->m_save_scene_browser->SetTitle("Save Scene");
    this->m_save_scene_browser->SetTypeFilters({ ".wah" });
}

ToolBar::~ToolBar()
{
    delete this->m_load_scene_browser;
    delete this->m_save_scene_browser;
}

void ToolBar::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        /* File Menus*/
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Scene"))
            {
                this->m_save_scene_browser->Open();
            }

            if (ImGui::MenuItem("Load Scene"))
            {
                this->m_load_scene_browser->Open();
            }

            ImGui::EndMenu();
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

    this->m_load_scene_browser->Display();
    this->m_save_scene_browser->Display();

    if (this->m_save_scene_browser->HasSelected())
    {
        SceneWriter writer = SceneWriter(this->m_save_scene_browser->GetSelected().string());
        writer.WriteToFile();

        this->m_save_scene_browser->ClearSelected();
        this->m_save_scene_browser->Close();
    }

    else if (this->m_load_scene_browser->HasSelected())
    {
        SceneReader reader = SceneReader(this->m_load_scene_browser->GetSelected().string());
        reader.ReadFromFile();

        this->m_load_scene_browser->ClearSelected();
        this->m_load_scene_browser->Close();
    }

    
}
