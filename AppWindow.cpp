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

	vec3 initialPos = { 0, 0, 0 };
	vec3 colorQuad = { 1, 1, 1 };

	Quad* obj = new Quad();
	obj->initialize(0.25f, 0.33f, initialPos, colorQuad);
	obj->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	obj->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
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

	unsigned long new_time = 0;

	if (m_old_time)
	{
		new_time = ::GetTickCount() - m_old_time;
	}

	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;

	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->updateConstantBuffer(&cc);
		objectList[i]->update(m_delta_time);
	}

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

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine::getInstance()->init();
}
