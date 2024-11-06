#pragma once
#include <vector>

#include "Window.h"

#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "InputSystem.h"

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObjectManager.h"
#include "InputListener.h"

#include "Cube.h"
#include "Plane.h"

class AppWindow : public Window, public InputListener
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

private:
	GameObjectManager* gameObjectManager = nullptr;
	GameObject* rotatedObject = nullptr;

	SwapChain* m_swap_chain = nullptr;

	bool backspacePressed = false;
	bool deletePressed = false;
	bool spacePressed = false;
	LONG m_window_width = 0;
	LONG m_window_height = 0;
	float m_ticks_translate = 0.0f;
	float m_ticks_scale = 0.0f;
	float elapsedTime = 0.0f;

	// Inherited via InputListener
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
};
