#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	XMFLOAT3 localPos = this->local_position;
	XMVECTOR position = XMLoadFloat3(&localPos);
	float p_x = XMVectorGetX(position);
	float p_y = XMVectorGetY(position);
	float p_z = XMVectorGetZ(position);
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		p_z += deltaTime * moveSpeed;
		this->setPosition(p_x, p_y, p_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		p_z -= deltaTime * moveSpeed;
		this->setPosition(p_x, p_y, p_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A'))
	{
		p_x -= deltaTime * moveSpeed;
		this->setPosition(p_x, p_y, p_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D'))
	{
		p_x += deltaTime * moveSpeed;
		this->setPosition(p_x, p_y, p_z);
		this->updateViewMatrix();
	}

	if (InputSystem::getInstance()->isKeyDown('R'))
	{ 
		isProjectionToggle = !isProjectionToggle;
	}
}

XMMATRIX Camera::getViewMatrix()
{
	return this->local_matrix;
}

XMMATRIX Camera::getProjectionMatrix()
{
	if (this->isProjectionToggle)
	{
		this->aspectRatio = this->width / this->height;
		return XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
	}

	this->view_width = this->width / 200.0f;
	this->view_height = this->height / 200.0f;

	return XMMatrixOrthographicOffCenterLH(-view_width, view_width, -view_height, view_height, -4.0f, 4.0f);
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const XMFLOAT2& mouse_pos)
{
	//XMFLOAT3 localRot = this->local_position;
	//XMVECTOR rotation = XMLoadFloat3(&localRot);
	//float r_x = XMVectorGetX(rotation);
	//float r_y = XMVectorGetY(rotation);
	//float r_z = XMVectorGetZ(rotation);
	//float sensitivity = 0.01f;

	//float xOffset = (mouse_pos.x - (width / 2.0f)) * sensitivity;
	//float yOffset = (mouse_pos.y - (height / 2.0f)) * sensitivity;

	//r_x += xOffset;
	//r_y += yOffset;

	////// Clamp pitch to prevent flipping
	////if (r_y > XM_PIDIV2 - 0.1f)
	////	r_y = XM_PIDIV2 - 0.1f;
	////if (r_x < -XM_PIDIV2 + 0.1f)
	////	r_x = -XM_PIDIV2 + 0.1f;

	//InputSystem::getInstance()->setCursorPosition(XMFLOAT2(width / 2.0f, height / 2.0f));
	//this->setRotation(r_x, r_y, r_z);
	//this->updateViewMatrix();
}

void Camera::onLeftMouseDown(const XMVECTOR& mouse_pos)
{
}

void Camera::onLeftMouseUp(const XMVECTOR& mouse_pos)
{
}

void Camera::onRightMouseDown(const XMVECTOR& mouse_pos)
{
}

void Camera::onRightMouseUp(const XMVECTOR& mouse_pos)
{
}

void Camera::setScreenParams(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Camera::updateViewMatrix()
{
	XMMATRIX world_matrix = this->getWorldMatrix();
	this->local_matrix = XMMatrixInverse(nullptr, world_matrix);
}

void Camera::draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
}
