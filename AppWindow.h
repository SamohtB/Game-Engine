#pragma once
#include <vector>

#include "Window.h"

#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "RenderSystem.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "ShaderLibrary.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "StateManager.h"
#include "ActionHistory.h"

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObjectManager.h"
#include "InputListener.h"

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

private:
	SwapChainPtr m_swap_chain = nullptr;

	LONG m_window_width = 0;
	LONG m_window_height = 0;
	float m_ticks_translate = 0.0f;
	float m_ticks_scale = 0.0f;
	float elapsedTime = 0.0f;

    bool my_tool_active = true;

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
