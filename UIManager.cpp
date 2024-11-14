#include "UIManager.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include "AUIScreen.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager::UIManager(HWND windowHandle)
{
    /* Initialization */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    /* Style */
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->getDirectXDevice(),
        GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->getContext());

    /* Populate */

}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    try
    {
        sharedInstance = new UIManager(windowHandle);
    }
    catch (...)
    {
        throw std::exception("UIManager not created successfully");
    }
}

void UIManager::destroy()
{
    delete sharedInstance;
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for(AUIScreen* ui : uiList)
    {
        ui->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

