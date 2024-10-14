#include "AppWindow.h"
#include <Windows.h>
#include <math.h>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	initializeEngine();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Updating the constant buffer with white spotlight parameters
	cc.light_position = { 0.0f, 5.0f, 5.0f };
	cc.light_intensity = 2.0f;
	cc.light_direction = { 0.0f, -5.0f, -5.0f };

	float length = sqrt(cc.light_direction.x * cc.light_direction.x +
		cc.light_direction.y * cc.light_direction.y +
		cc.light_direction.z * cc.light_direction.z);
	cc.light_direction.x /= length;
	cc.light_direction.y /= length;
	cc.light_direction.z /= length;

	cc.spec_phong = 64.0f;                       
	cc.light_color = { 1.0f, 1.0f, 1.0f };             
	cc.spec_strength = 0.5f;                          
	cc.light_ambient_color = { 0.1f, 0.1f, 0.1f };     
	cc.light_ambient_strength = 0.5f;                  
	cc.range = 100.0f;                                  
	cc.inner_angle = 30.0f * (3.14159f / 180.0f);
	cc.outer_angle = 60.0f * (3.14159f / 180.0f);
	cc.attenuation = 0.1f;                             

	Quad* obj = new Quad();
	
	/* background quad */
	obj->setParameters(0.9f, 0.9f, { 0.f, 0.f, 0.f }, { 0.3f, 0.3f, 0.3f });
	obj->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "unlit");
	obj->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	objectList.push_back((GameObject*)obj);

	/* top left quad */
	obj = new Quad();
	obj->setParameters(0.15f, 0.15f, { 0.7f, 0.7f, 0.f }, { 1.f, 0.f, 0.f });
	obj->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	obj->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	objectList.push_back((GameObject*)obj);

	/* center quad */
	obj = new Quad();
	obj->setParameters(0.15f, 0.15f, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });
	obj->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	obj->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	objectList.push_back((GameObject*)obj);

	/* bottom right quad */
	obj = new Quad();
	obj->setParameters(0.15f, 0.15f, { -0.7f, -0.7f, 0.f }, { 0.f, 0.f, 1.f });
	obj->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	obj->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	objectList.push_back((GameObject*)obj);

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
