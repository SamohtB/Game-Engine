#include "AppWindow.h"
#include <Windows.h>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//vertex list[] =
	//{
	//	//X - Y - Z
	//	{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
	//	{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
	//	{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
	//	{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	//};

	vertex rainbow_square[] =
	{
		{-0.5f, -0.5f, 0.0f,    -0.32f, -0.11f, 0.0f,	1, 0, 0,	0, 0, 1},
		{-0.5f,  0.5f, 0.0f,    -0.11f,  0.78f, 0.0f,	1, 1, 0,	0, 1, 0},
		{0.5f,  -0.5f, 0.0f,     0.75f, -0.73f, 0.0f,	0, 1, 0,	1, 1, 0},
		{0.5f,   0.5f, 0.0f,     0.88f,  0.77f, 0.0f,	0, 0, 1,	1, 0, 0}
	};

	//vertex rainbow_triagle[] =
	//{

	//	{-0.25f,-0.25f,0.0f,	1, 0, 0},
	//	{ 0.0f,0.25f,0.0f,		0, 1, 0},
	//	{ 0.25f,-0.25f,0.0f,	0, 0, 1}
	//};

	//vertex square_green[] =
	//{
	//	{0.5f,-0.25f,0.0f,  	0, 1, 0},
	//	{0.5f,0.25f,0.0f,	    0, 1, 0},
	//	{0.75f,-0.25f,0.0f,     0, 1, 0},
	//	{0.75f,0.25f,0.0f, 		0, 1, 0},

	//};

	objectList.push_back((GameObject*) new Quad(rainbow_square));
	//objectList.push_back((GameObject*) new Quad(square_green));
	//objectList.push_back((GameObject*) new Triangle(rainbow_triagle));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	/* Clear Render Target */
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	/* Render Target Viewport */
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

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

	//for (int i = 0; i < objectList.size(); i++)
	//{
		objectList[0]->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
		objectList[0]->draw();
	//}

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
	GraphicsEngine::get()->release();
}
