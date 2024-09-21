#pragma once
#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObject.h"
#include "Quad.h"
#include "Triangle.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	SwapChain* m_swap_chain = nullptr;

	std::vector<GameObject*> objectList;

	//VertexBuffer* m_vb = nullptr;
	//VertexShader* m_vs = nullptr;
	//PixelShader* m_ps = nullptr;
};
