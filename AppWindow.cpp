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

	vertex pos1[] =
	{
		//X - Y - Z
		{-0.75f,-0.75f,0.0f}, // POS1
		{-0.75f,0.75f,0.0f}, // POS2
		{ -0.5f,-0.75f,0.0f },// POS2
		{ -0.5f,0.75f,0.0f}
	};

	vertex pos2[] =
	{
		//X - Y - Z
		{0.75f,-0.75f,0.0f}, // POS1
		{0.75f,0.75f,0.0f}, // POS2
		{ 0.5f,-0.75f,0.0f },// POS2
		{ 0.5f,0.75f,0.0f}
	};

	Quad* quad = new Quad(pos1);
	objectList[0] = (GameObject*)quad;
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);


	objectList[0]->draw(GraphicsEngine::get()->getImmediateDeviceContext()->getContext());


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
