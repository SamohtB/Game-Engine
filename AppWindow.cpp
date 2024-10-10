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

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain->init(this->m_hwnd, this->m_window_width, this->m_window_height);

	Circle* circle = new Circle(0.05f, XMFLOAT3(1.f, 1.f, 1.f));
	circle->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	circle->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	objectList.push_back(circle);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.f, 0.f, 0.f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	/* Inputs */
	handleKeyInputs();

	/* Updates */
	updateGameObjects();

	/* Draws */
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->release();
	}	
	GraphicsEngine::destroy();
}

void AppWindow::updateGameObjects()
{
	float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

	float viewWidth = this->m_window_width / 200.0f;
	float viewHeight = this->m_window_height / 200.0f;

	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->setWindowParameters(viewWidth, viewHeight);
		objectList[i]->update(deltaTime);
	}
}

void AppWindow::handleKeyInputs()
{
}

