#pragma once
#include <vector>

#include "Window.h"

#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObjectManager.h"
#include "InputListener.h"

#include "Cube.h"
#include "Plane.h"
#include "Quad.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	void updateGameObjects();
	void drawGameObjects();

private:
	GameObjectManager* gameObjectManager = nullptr;
	Quad* fullQuad = nullptr;

	SwapChain* m_swap_chain = nullptr;

	LONG m_window_width = 0;
	LONG m_window_height = 0;
	float m_ticks_translate = 0.0f;
	float m_ticks_scale = 0.0f;
	float elapsedTime = 0.0f;

	// Inherited via InputListener
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	// Inherited via InputListener
	void onMouseMove(const XMFLOAT2& mouse_pos) override;
	void onLeftMouseDown(const XMVECTOR& mouse_pos) override;
	void onLeftMouseUp(const XMVECTOR& mouse_pos) override;
	void onRightMouseDown(const XMVECTOR& mouse_pos) override;
	void onRightMouseUp(const XMVECTOR& mouse_pos) override;
};
