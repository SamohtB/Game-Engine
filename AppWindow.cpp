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

	EngineTime::setFrameTime(60);
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(false);

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain->init(this->m_hwnd, this->m_window_width, this->m_window_height);

	SceneCameraHandler::getInstance()->setScreenSize((float)m_window_width, (float)m_window_height);

	Cube* cube = nullptr;
	this->gameObjectManager = new GameObjectManager();

	for (int i = 0; i < 5; i++)
	{
		Cube* cube = new Cube();
		cube->setSize(0.15f);
		cube->initialize();
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
		gameObjectManager->registerObject(cube);
	}
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3f, 0.2f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	/* Inputs */
	SceneCameraHandler::getInstance()->update();
	InputSystem::getInstance()->update();

	/* Updates */
	updateGameObjects();

	/* Draws */
	drawGameObjects();

	m_swap_chain->present(true);
}

void AppWindow::updateGameObjects()
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());
	
	XMMATRIX viewMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	XMMATRIX projectionMatrix = SceneCameraHandler::getInstance()->getSceneCameraProjMatrix();

	gameObjectManager->setViewMatrix(viewMatrix);
	gameObjectManager->setProjectionMatrix(projectionMatrix);
	gameObjectManager->update(deltaTime);
}

void AppWindow::drawGameObjects()
{
	gameObjectManager->draw(this->m_window_width, this->m_window_height);
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
	m_swap_chain->release();
	GraphicsEngine::destroy();
	InputSystem::destroy();
	SceneCameraHandler::destroy();
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