#pragma once
#include "AUIScreen.h"
#include "imfilebrowser.h"

class ToolBar : public AUIScreen
{
public:
    ToolBar();
    ~ToolBar();

    // Inherited via AUIScreen
    void drawUI() override;

    void drawLoadSceneWindow();

    void drawSaveSceneWindow();

private:
    /* Default Save Directory */
    const std::string m_scene_directory = "Scenes/";

    /* Holds max file path and name char  for input */
    char saveFileName[128] = "Test_Scene";
    char loadFileName[128] = "Test_Scene";

    ImGui::FileBrowser* m_save_scene_browser;
    ImGui::FileBrowser* m_load_scene_browser;
};

