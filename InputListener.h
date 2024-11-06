#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class InputListener
{
public:
	InputListener()
	{

	}

	~InputListener()
	{

	}

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	virtual void onMouseMove(const XMFLOAT2& delta_mouse_pos) = 0;

	virtual void onLeftMouseDown(const XMVECTOR& mouse_pos) = 0;
	virtual void onLeftMouseUp(const XMVECTOR& mouse_pos) = 0;

	virtual void onRightMouseDown(const XMVECTOR& mouse_pos) = 0;
	virtual void onRightMouseUp(const XMVECTOR& mouse_pos) = 0;
};