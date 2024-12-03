#include "AppWindow.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <random>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();

	/* Engine Component Initialization */
	EngineTime::initialize();
	InputSystem::initialize();
	
	GraphicsEngine::initialize();
    UIManager::initialize(this->m_hwnd);
    GameObjectManager::initialize();
    ShaderLibrary::initialize();

    this->m_physics_system = new PhysicsSystem();

	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, this->m_window_width, this->m_window_height);

    SceneCameraHandler::initialize(static_cast<float>(m_window_width), static_cast<float>(m_window_height));
    EngineTime::setFrameTime(60);
    InputSystem::getInstance()->addListener(this);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3f, 0.2f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	/* Inputs */
	SceneCameraHandler::getInstance()->update();
	InputSystem::getInstance()->update();

	/* Updates */
    GameObjectManager::getInstance()->updateAll();

	/* Draws */
    GameObjectManager::getInstance()->renderAll(this->m_window_width, this->m_window_height);
    UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onKeyDown(int key) {}

void AppWindow::onKeyUp(int key) {}

void AppWindow::onMouseMove(const XMFLOAT2& mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const XMVECTOR& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const XMVECTOR& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const XMVECTOR& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const XMVECTOR& mouse_pos)
{
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::destroy();
	InputSystem::destroy();
	SceneCameraHandler::destroy();
    UIManager::destroy();
    ShaderLibrary::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->addListener(SceneCameraHandler::getInstance()->getCamera());
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->removeListener(SceneCameraHandler::getInstance()->getCamera());
}
