#pragma once
#include "AUIScreen.h"

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

    bool m_save_window = false;
    bool m_load_window = false;
};

