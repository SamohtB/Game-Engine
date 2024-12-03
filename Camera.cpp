#include "Camera.h"
#include <algorithm>
#include <iostream>

Camera::Camera(String name, float width, float height) : AGameObject(name), m_viewport_width(width), m_viewport_height(height)
{
    this->setActive(true);
    this->setObjectType(CAMERA);
    this->m_last_mouse_position = XMFLOAT2(0, 0);
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
    XMVECTOR position = XMLoadFloat3(&this->m_local_position);
    XMVECTOR rotation = XMLoadFloat3(&this->m_local_rotation);

    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYawFromVector(rotation);
    XMVECTOR forward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), rotationMatrix);
    XMVECTOR right = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), rotationMatrix);

    XMVECTOR moveDirection = XMVectorZero();

    if (InputSystem::getInstance()->isKeyDown('W'))
    {
        moveDirection += forward;
    }
    if (InputSystem::getInstance()->isKeyDown('S'))
    {
        moveDirection -= forward;
    }
    if (InputSystem::getInstance()->isKeyDown('A'))
    {
        moveDirection -= right;
    }
    if (InputSystem::getInstance()->isKeyDown('D'))
    {
        moveDirection += right;
    }
    if (InputSystem::getInstance()->isKeyDown(VK_SPACE))
    {
        moveDirection += XMVectorSet(0, 1, 0, 0);
    }
    if (InputSystem::getInstance()->isKeyDown(VK_LSHIFT))
    {
        moveDirection -= XMVectorSet(0, 1, 0, 0);
    }

    if (!XMVector3Equal(moveDirection, XMVectorZero()))
    {
        moveDirection = XMVector3Normalize(moveDirection);
    }

    moveDirection *= m_move_speed * deltaTime;
    this->setPosition(position + moveDirection);
    this->updateViewMatrix();
}

XMMATRIX Camera::getViewMatrix()
{
	return this->m_local_matrix;
}

XMMATRIX Camera::getProjectionMatrix()
{
	if (this->isProjectionToggle)
	{
		this->aspectRatio = this->m_viewport_width / this->m_viewport_height;
		return XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspectRatio, nearZ, farZ);
	}

	return XMMatrixOrthographicOffCenterLH(-this->m_viewport_width / 200.0f, this->m_viewport_width / 200.0f, -m_viewport_height / 200.0f, m_viewport_height / 200.0f, -4.0f, 4.0f);
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const XMFLOAT2& mouse_pos)
{
    if (m_right_mouse_pressed)
    {
        float deltaYaw = (mouse_pos.x - this->m_last_mouse_position.x) * 0.01f;
        float deltaPitch = (mouse_pos.y - this->m_last_mouse_position.y) * 0.01f;

        deltaYaw = std::clamp(deltaYaw, -89.0f, 89.0f);

        this->rotate(deltaPitch, deltaYaw, 0.0f);
    }

    this->m_last_mouse_position = mouse_pos;
    this->updateViewMatrix();
}

void Camera::onLeftMouseDown(const XMVECTOR& mouse_pos)
{
}

void Camera::onLeftMouseUp(const XMVECTOR& mouse_pos)
{
}

void Camera::onRightMouseDown(const XMVECTOR& mouse_pos)
{
    m_right_mouse_pressed = true;
    XMStoreFloat2(&m_last_mouse_position, mouse_pos);
}

void Camera::onRightMouseUp(const XMVECTOR& mouse_pos)
{
    m_right_mouse_pressed = false;
}

void Camera::setScreenParams(float width, float height)
{
	this->m_viewport_width = width;
	this->m_viewport_height = height;
}

void Camera::updateViewMatrix()
{
    XMVECTOR position = this->getLocalPosition();
    XMVECTOR rotation = this->getLocalRotation();
    XMVECTOR scale = this->getLocalScale();

    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(position);
    XMMATRIX scaleMatrix = XMMatrixScalingFromVector(scale);

    XMMATRIX rotationMatrixX = XMMatrixRotationX(XMVectorGetX(rotation));
    XMMATRIX rotationMatrixY = XMMatrixRotationY(XMVectorGetY(rotation));
    XMMATRIX rotationMatrixZ = XMMatrixRotationZ(XMVectorGetZ(rotation));

    XMMATRIX rotationMatrix = XMMatrixMultiply(rotationMatrixX, XMMatrixMultiply(rotationMatrixY, rotationMatrixZ));
    XMMATRIX worldMatrix = XMMatrixMultiply(scaleMatrix, XMMatrixMultiply(rotationMatrix, translationMatrix));

    this->m_local_matrix = XMMatrixInverse(nullptr, worldMatrix);
}

void Camera::draw(int width, int height)
{
}
