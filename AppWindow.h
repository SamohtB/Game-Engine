#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	SwapChain* m_swap_chain = nullptr;
	VertexBuffer* m_vb = nullptr;
	VertexShader* m_vs = nullptr;
};
