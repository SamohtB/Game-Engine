#pragma once
#include <vector>

#include "Window.h"

#include "GraphicsEngine.h"
#include "EngineTime.h"

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

	void initializeEngine();
	

private:
	std::vector<GameObject*> objectList;

	SwapChain* m_swap_chain = nullptr;

	constant cc;
	float elapsedTime = 0.0f;
};
