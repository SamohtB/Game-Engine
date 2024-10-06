#include "AppWindow.h"
#include <Windows.h>
#include <algorithm>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::initialize();
	EngineTime::initialize();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*vertex looped_quad[] =
	{
		{-0.7f, -0.9f, 0.0f,    -0.32f, -0.11f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
		{-0.8f,  0.2f, 0.0f,    -0.11f,  0.78f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
		{0.3f,  -0.3f, 0.0f,     0.75f, -0.73f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
		{0.0f,   0.2f, 0.0f,     0.88f,  0.77f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f}
	};

	Quad* quad = new Quad();
	quad->setShaders(looped_quad, &cc);

	objectList.push_back((GameObject*) quad);*/

	vertex folding_quad[] =
	{
		{-0.8f, -1.0f, 0.0f, -0.5f, -0.5f, 0.0f,	1.f, 1.f, 0.f,	1.f, 1.f, 0.f}, // top left
		{-1.0f,  0.0f, 0.0f, -0.1f,  0.7f, 0.0f,	1.f, 1.f, 1.f,	0.f, 0.f, 1.f}, //top right
		{ 1.0f, -0.2f, 0.0f,  0.2f, -0.5f, 0.0f, 	0.f, 0.f, 1.f,	1.f, 0.f, 0.f}, //bottom left
		{-0.8f, -1.0f, 0.0f,  0.7f,  0.7f, 0.0f,	0.f, 0.f, 0.f,	0.f, 1.f, 0.f},	//topleft
	};

	Quad* quad = new Quad();
	quad->setShaders(folding_quad, &cc);

	objectList.push_back((GameObject*)quad);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	elapsedTime += static_cast<float>(EngineTime::getDeltaTime());
	cc.deltaTime = elapsedTime;

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
