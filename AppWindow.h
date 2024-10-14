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

#include "CircleManager.h"
#include "Cube.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void handleKeyInputs();
	void updateGameObjects();
	void drawGameObjects();

	constant calculateConstants(float deltaTime);

private:
	std::vector<GameObject*> objectList;

	SwapChain* m_swap_chain = nullptr;
	CircleManager* circleManager = nullptr;

	bool backspacePressed = false;
	bool deletePressed = false;
	bool spacePressed = false;
	LONG m_window_width = 0;
	LONG m_window_height = 0;
	float m_ticks_translate = 0.0f;
	float m_ticks_scale = 0.0f;
	float elapsedTime = 0.0f;
};
