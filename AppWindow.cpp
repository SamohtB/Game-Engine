#include "AppWindow.h"
#include <Windows.h>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	initializeEngine();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	cc.directionalLightDir = { 1.0f, 1.0f, 1.0f, 1.0f };
	cc.directionalLightColor = { 1.0f, 0.68f, 0.8f, 1.0f };
	cc.directionalLightAmbientColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	cc.lightParameters = { 0.5f, 64.0f, 0.5f, 2.0f };  // x = ambientStr, y = specPhong, z = specStr, w = dirLightIntensity
	cc.cameraPos = { 0.0f, 0.0f, 5.0f, 0.0f};

	vertex middle_square[] =
	{
		{-0.25f, -0.33f, 0.0f,  1, 1, 1},
		{-0.25f,  0.33f, 0.0f,  1, 1, 1},
		{0.25f,  -0.33f, 0.0f,  1, 1, 1},
		{0.25f,   0.33f, 0.0f,  1, 1, 1}
	};

	Quad* obj = new Quad();
	obj->createShaders(middle_square, &cc);
	objectList.push_back((GameObject*) obj);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	/* Clear Render Target */
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	/* Render Target Viewport */
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
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

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine::getInstance()->init();
}
