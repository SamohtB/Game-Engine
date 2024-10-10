#include "AppWindow.h"
#include <Windows.h>
#include <algorithm>

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

	/*FoldingQuad* folding_quad = new FoldingQuad();
	folding_quad->initialize(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	folding_quad->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	objectList.push_back(static_cast<GameObject*>(folding_quad));*/

	/*LoopedQuad* looped_quad = new LoopedQuad();
	looped_quad->initialize(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	looped_quad->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	objectList.push_back(static_cast<GameObject*>(looped_quad));*/

	Quad* quad = new Quad();
	quad->initialize(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	quad->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	objectList.push_back(static_cast<GameObject*>(quad));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	updateGameObjects();

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
	constant cc;
	float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

	elapsedTime += deltaTime;
	cc.elapsedTime = elapsedTime;

	this->m_ticks_translate += deltaTime / 4.0f;

	if (m_ticks_translate > 1.0f)
	{
		m_ticks_translate = 0.0f;
	}

	this->m_ticks_scale += deltaTime * 1.0f;

	Matrix4x4 temp;

	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.5f, 1.5f, 0), (sin(m_ticks_scale) + 1.0f) / 2.0f));
	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_ticks_translate));

	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection_matrix.setOrthogonalProjectionMatrix(this->m_window_width / 200.0f, this->m_window_height / 200.0f, -4.0f, 4.0f);

	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	}
}
