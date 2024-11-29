#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(String name);
	~Camera();

	void update(float deltaTime) override;
	XMMATRIX getViewMatrix();
	XMMATRIX getProjectionMatrix();

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const XMFLOAT2& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const XMVECTOR& mouse_pos) override;
	virtual void onLeftMouseUp(const XMVECTOR& mouse_pos) override;

	virtual void onRightMouseDown(const XMVECTOR& mouse_pos) override;
	virtual void onRightMouseUp(const XMVECTOR& mouse_pos) override;

	void setScreenParams(float width, float height);

private:
	void updateViewMatrix();

	// Inherited via GameObject
	void draw(int width, int height) override;

	bool isProjectionToggle = true;
	float width = 0;
	float height = 0;

	float fov = XM_PIDIV4;
	float aspectRatio = 0.0f;
	float nearZ = 0.01f;
	float farZ = 100.0f;

	float view_width = 0;
	float view_height = 0;
};
