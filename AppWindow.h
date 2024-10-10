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
#include "Quads.h"
#include "Circle.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	void updateGameObjects();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void handleKeyInputs();

private:
	std::vector<GameObject*> objectList;

	SwapChain* m_swap_chain = nullptr;

	LONG m_window_width = 0;
	LONG m_window_height = 0;
	float m_ticks_translate = 0.0f;
	float m_ticks_scale = 0.0f;
	float elapsedTime = 0.0f;
};
