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
	GraphicsEngine::initialize();
	EngineTime::initialize();

	EngineTime::setFrameTime(60);
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain->init(this->m_hwnd, this->m_window_width, this->m_window_height);

	Cube* cube = nullptr;
	this->gameObjectManager = new GameObjectManager();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> posDist(-0.75f, 0.75f);
	std::uniform_real_distribution<float> speedDist(-2.0f, 2.0f);

	for (int i = 0; i < 1; i++)
	{
		cube = new Cube();
		cube->setSize(0.15f);
		cube->initialize();
		cube->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
		cube->setPosition(XMVECTOR{ 0, 0.25, 0 });
		cube->setSpeed(speedDist(gen));
		gameObjectManager->registerObject(cube);
	}

	Plane* plane = new Plane();
	plane->setSize(0.45f);
	plane->initialize();
	plane->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	plane->setPosition(XMVECTOR{ 0, 0, 0 });
	gameObjectManager->registerObject(plane);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3f, 0.2f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	/* Inputs */
	handleKeyInputs();

	/* Updates */
	updateGameObjects();

	/* Draws */
	drawGameObjects();

	m_swap_chain->present(true);
}

void AppWindow::handleKeyInputs()
{
}

void AppWindow::updateGameObjects()
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());

	gameObjectManager->update(deltaTime);
	gameObjectManager->draw(this->m_window_width, this->m_window_height);
}

void AppWindow::drawGameObjects()
{
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::destroy();
}





