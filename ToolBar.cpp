#include "ToolBar.h"

ToolBar::ToolBar() : AUIScreen("Tool Bar") {}

ToolBar::~ToolBar() {}

void ToolBar::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        /* File Menus*/
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New", NULL, &m_show_new_file);
            ImGui::MenuItem("Open", NULL, &m_show_open);
            ImGui::MenuItem("Save", NULL, &m_show_save);
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
    
}
