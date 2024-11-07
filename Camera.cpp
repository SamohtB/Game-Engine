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
}

XMMATRIX Camera::getViewMatrix()
{
	return this->local_matrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const XMFLOAT2& delta_mouse_pos)
{
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

void Camera::updateViewMatrix()
{
	XMMATRIX world_matrix = this->getWorldMatrix();
	this->local_matrix = XMMatrixInverse(nullptr, world_matrix);
}

void Camera::initialize()
{
}

void Camera::draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
}
