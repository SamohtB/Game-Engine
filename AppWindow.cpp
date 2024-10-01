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

	vertex left_square[] =
	{
		{-0.75f, -0.33f, 0.0f,  -0.75f, -0.67f, 0.0f,	1, 0, 0,	0, 0, 1},
		{-0.75f,  0.33f, 0.0f,  -0.75f,  0.67f, 0.0f,	1, 1, 0,	0, 1, 0},
		{-0.4f, -0.33f, 0.0f,   -0.4f,  -0.67f, 0.0f,	0, 1, 0,	1, 1, 0},
		{-0.4f,  0.33f, 0.0f,	-0.4f,   0.67f, 0.0f,	0, 0, 1,	1, 0, 0}
	};

	objectList.push_back((GameObject*) new Quad(left_square));

	vertex middle_square[] =
	{
		{-0.25f, -0.33f, 0.0f,    -0.25f, -0.67f, 0.0f,		1, 0, 0,	0, 0, 1},
		{-0.25f,  0.33f, 0.0f,    -0.25f,  0.67f, 0.0f,		1, 1, 0,	0, 1, 0},
		{0.25f,  -0.33f, 0.0f,     0.25f, -0.67f, 0.0f,		0, 1, 0,	1, 1, 0},
		{0.25f,   0.33f, 0.0f,     0.25f,  0.67f, 0.0f,		0, 0, 1,	1, 0, 0}
	};

	objectList.push_back((GameObject*) new Quad(middle_square));

	vertex right_square[] =
	{
		{0.4f, -0.33f, 0.0f,    0.4f,	-0.67f, 0.0f,	0, 1, 0,	1, 1, 0},
		{0.4f,  0.33f, 0.0f,    0.4f,	 0.67f, 0.0f,	0, 0, 1,	1, 0, 0},
		{0.75f, -0.33f, 0.0f,   0.75f,	-0.67f, 0.0f,	1, 0, 0,	0, 0, 1},
		{0.75f,  0.33f, 0.0f,   0.75f,	 0.67f, 0.0f,	1, 1, 0,	0, 1, 0},
	};
	
	objectList.push_back((GameObject*) new Quad(right_square));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	/* Clear Render Target */
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	/* Render Target Viewport */
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
	{
		new_time = ::GetTickCount() - m_old_time;
	}
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

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
