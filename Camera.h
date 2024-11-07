#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "InputSystem.h"

class Camera : public GameObject, public InputListener
{
public:
	Camera();
	~Camera();

	void update(float deltaTime) override;
	XMMATRIX getViewMatrix();

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const XMFLOAT2& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const XMVECTOR& mouse_pos) override;
	virtual void onLeftMouseUp(const XMVECTOR& mouse_pos) override;

	virtual void onRightMouseDown(const XMVECTOR& mouse_pos) override;
	virtual void onRightMouseUp(const XMVECTOR& mouse_pos) override;

private:
	void updateViewMatrix();

	// Inherited via GameObject
	void initialize() override;
	void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix) override;
};