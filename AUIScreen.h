#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

typedef std::string String;
class UIManager;

class AUIScreen
{
public:
    AUIScreen(String name);
    ~AUIScreen();

protected:
    typedef std::string String;

    String getName();
    virtual void drawUI() = 0;

    String name;

    friend class UIManager;
};

