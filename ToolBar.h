#pragma once
#include "AUIScreen.h"
class ToolBar : public AUIScreen
{
public:
    ToolBar();
    ~ToolBar();

    // Inherited via AUIScreen
    void drawUI() override;

private:
    bool m_is_shown = true;
    bool m_show_new_file = true;
    bool m_show_open = true;
    bool m_show_save = true;
};

