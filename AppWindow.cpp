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

	//FoldingQuad* folding_quad = new FoldingQuad();
	//folding_quad->initialize(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	//folding_quad->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//objectList.push_back(static_cast<GameObject*>(folding_quad));

	LoopedQuad* looped_quad = new LoopedQuad();
	looped_quad->initialize(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	looped_quad->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	objectList.push_back(static_cast<GameObject*>(looped_quad));
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
