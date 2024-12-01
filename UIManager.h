#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <Windows.h>

#include "AUIScreen.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

class UINames
{
public:
    const String TOOL_BAR = "TOOL_BAR";
    const String HIERARCHY = "HIERARCHY";
    const String INSPECTOR = "INSPECTOR";
};

class UIManager
{
public:
    typedef std::string String;
    typedef std::vector<AUIScreen*> UIList;
    typedef std::unordered_map<String, AUIScreen*> UITable;

    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawAllUI();

    static const int WINDOW_WIDTH = 1024;
    static const int WINDOW_HEIGHT = 768;

private:
    UIManager(HWND windowHandle);
    ~UIManager();
    UIManager(UIManager const&) {}
    UIManager& operator=(UIManager const&) {}

    static UIManager* sharedInstance;

    UIList uiList;
    UITable uiTable;

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
};

