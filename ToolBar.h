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
};

