#include "AppWindow.h"

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex rainbow_square[] =
	{
		{-0.75f, -0.25f, 0.0f,   1, 0, 0},       
		{-0.75f,  0.25f, 0.0f,   1, 1, 0},     
		{-0.5f,  -0.25f, 0.0f,   0, 1, 0},       
		{-0.5f,   0.25f, 0.0f,   0, 0, 1}        
	};

	vertex rainbow_triagle[] =
	{

		{-0.25f,-0.25f,0.0f,	1, 0, 0},
		{ 0.0f,0.25f,0.0f,		0, 1, 0},
		{ 0.25f,-0.25f,0.0f,	0, 0, 1}
	};

	vertex square_green[] =
	{
		{0.5f,-0.25f,0.0f,  	0, 1, 0},
		{0.5f,0.25f,0.0f,	    0, 1, 0},
		{0.75f,-0.25f,0.0f,     0, 1, 0},
		{0.75f,0.25f,0.0f, 		0, 1, 0},

	};

	objectList.push_back((GameObject*) new Quad(rainbow_square));
	objectList.push_back((GameObject*) new Quad(square_green));
	objectList.push_back((GameObject*) new Triangle(rainbow_triagle));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	/* Clear Render Target */
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	/* Render Target Viewport */
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < 3; i++)
	{
		objectList[i]->draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
