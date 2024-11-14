#include "GameObject.h"


GameObject::GameObject() 
{
	this->local_position = XMFLOAT3(0, 0, 0);
	this->local_rotation = XMFLOAT3(0, 0, 0);
	this->local_scale = XMFLOAT3(1, 1, 1);
    this->local_matrix = XMMatrixIdentity();
}

GameObject::~GameObject() {}

void GameObject::update(float deltaTime) {}

void GameObject::setPosition(float x, float y, float z)
{
	local_position = XMFLOAT3(x, y, z);
}

void GameObject::setPosition(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_position, vector);
}

XMVECTOR GameObject::getLocalPosition()
{
	return XMLoadFloat3(&this->local_position);
}

void GameObject::setRotation(float pitch, float yaw, float roll)
{
	local_rotation = XMFLOAT3(pitch, yaw, roll);
}

void GameObject::setRotation(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_rotation, vector);
}

void GameObject::rotate(float pitch, float yaw, float roll)
{
	XMVECTOR currentRotation = XMLoadFloat3(&this->local_rotation);
	XMVECTOR newRotation = XMVectorSet(pitch, yaw, roll, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentRotation, newRotation);
	XMStoreFloat3(&this->local_rotation, combinedRotation);
}

XMVECTOR GameObject::getLocalRotation()
{
	return XMLoadFloat3(&this->local_rotation);
}

void GameObject::setScale(float x, float y, float z)
{
	local_scale = XMFLOAT3(x, y, z);
}

void GameObject::setScale(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_scale, vector);
}

void GameObject::scale(float scale)
{
	XMVECTOR currentScale = XMLoadFloat3(&this->local_scale);
	XMVECTOR newScale = XMVectorSet(scale, scale, scale, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentScale, newScale);
	XMStoreFloat3(&this->local_scale, combinedRotation);
}

XMVECTOR GameObject::getLocalScale()
{
	return XMLoadFloat3(&this->local_scale);
}

XMMATRIX GameObject::getWorldMatrix() const
{
	XMMATRIX matScale = XMMatrixScaling(local_scale.x, local_scale.y, local_scale.z);
	XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(local_rotation.x, local_rotation.y, local_rotation.z);
	XMMATRIX matTranslation = XMMatrixTranslation(local_position.x, local_position.y, local_position.z);

	return matScale * matRotation * matTranslation;
}

bool GameObject::isActive()
{
	return this->active;
}

void GameObject::setActive(bool value)
{
	this->active = value;
}
