#include "AppWindow.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>

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

	this->circleManager = new CircleManager();
	//this->circleManager->setSpeed(0.5f);
	//this->circleManager->CreateCirclePool(100);
	//this->circleManager->spawnBatch(5);

	Cube* cube = new Cube();
	cube->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	cube->setTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	objectList.push_back(cube);
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

void AppWindow::drawGameObjects()
{
	this->circleManager->draw();

	for (GameObject* object : this->objectList)
	{
		object->draw();
	}
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	delete this->circleManager;
	GraphicsEngine::destroy();
}

void AppWindow::updateGameObjects()
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());

	float viewWidth = this->m_window_width / 200.0f;
	float viewHeight = this->m_window_height / 200.0f;

	this->circleManager->setWindowParameters(viewWidth, viewHeight);
	this->circleManager->update(deltaTime);

	for (GameObject* object : this->objectList)
	{
		object->setWindowParameters(viewWidth, viewHeight);
		object->update(deltaTime);
	}
}

void AppWindow::handleKeyInputs()
{
	if (isBackspace())
	{
		if (!backspacePressed)
		{
			this->circleManager->clearNewestCircle();
			backspacePressed = true;
		}
	}
	else
	{
		backspacePressed = false;
	}

	if (isDelete())
	{
		if (!deletePressed)
		{
			this->circleManager->clearCircles();
			deletePressed = true;
		}
	}
	else
	{
		deletePressed = false;
	}

	if (isSpace())
	{
		if (!spacePressed)
		{
			this->circleManager->spawnBatch(1);
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
}

