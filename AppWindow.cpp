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
	InputSystem::initialize();

	EngineTime::setFrameTime(60);
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	InputSystem::getInstance()->addListener(this);
	
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

	rotatedObject = cube;

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
	InputSystem::getInstance()->update();

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

void AppWindow::onKeyDown(int key)
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());
	static float speed = 3.14f;

	if (key == 'W')
	{
		rotatedObject->rotate(speed * deltaTime, 0.0f, 0.0f);
	}

	else if (key == 'S')
	{
		rotatedObject->rotate(speed * deltaTime * -1.0f, 0.0f, 0.0f);
	}

	if (key == 'A')
	{
		rotatedObject->rotate(0.0f, 0.0f, speed * deltaTime);
	}

	else if (key == 'D')
	{
		rotatedObject->rotate(0.0f, 0.0f, speed * deltaTime * -1.0f);
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::destroy();
	InputSystem::destroy();
}





