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
	SceneCameraHandler::initialize();
	GraphicsEngine::initialize();
    UIManager::initialize(this->m_hwnd);
    GameObjectManager::initialize();

	EngineTime::setFrameTime(60);
	InputSystem::getInstance()->addListener(this);

	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, this->m_window_width, this->m_window_height);

	SceneCameraHandler::getInstance()->setScreenSize((float)m_window_width, (float)m_window_height);

	Cube* cube = nullptr;

	for (int i = 0; i < 5; i++)
	{
		Cube* cube = new Cube(0.15f);
		cube->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");

		XMVECTOR position;

		if (i == 0) {
			position = XMVectorSet(-0.5f, -0.5f, 0.0f, 0.0f);  // Bottom-left corner
		}
		else if (i == 1) {
			position = XMVectorSet(0.5f, -0.5f, 0.0f, 0.0f);   // Bottom-right corner
		}
		else if (i == 2) {
			position = XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f);    // Top-right corner
		}
		else if (i == 3) {
			position = XMVectorSet(-0.5f, 0.5f, 0.0f, 0.0f);   // Top-left corner
		}
		else {
			position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);    // Center of the space
		}

		cube->setPosition(position);
		GameObjectManager::getInstance()->addGameObject(cube);
	}
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
    UIManager::getInstance()->drawAllUI();
    GameObjectManager::getInstance()->renderAll(this->m_window_width, this->m_window_height,
        SceneCameraHandler::getInstance()->getSceneCameraViewMatrix(), SceneCameraHandler::getInstance()->getSceneCameraProjMatrix());

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
