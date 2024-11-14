#include "GameObject.h"


AGameObject::AGameObject() 
{
	this->local_position = XMFLOAT3(0, 0, 0);
	this->local_rotation = XMFLOAT3(0, 0, 0);
	this->local_scale = XMFLOAT3(1, 1, 1);
    this->local_matrix = XMMatrixIdentity();
}

AGameObject::~AGameObject() {}

void AGameObject::update(float deltaTime) {}

void AGameObject::setPosition(float x, float y, float z)
{
	local_position = XMFLOAT3(x, y, z);
}

void AGameObject::setPosition(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_position, vector);
}

XMVECTOR AGameObject::getLocalPosition()
{
	return XMLoadFloat3(&this->local_position);
}

void AGameObject::setRotation(float pitch, float yaw, float roll)
{
	local_rotation = XMFLOAT3(pitch, yaw, roll);
}

void AGameObject::setRotation(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_rotation, vector);
}

void AGameObject::rotate(float pitch, float yaw, float roll)
{
	XMVECTOR currentRotation = XMLoadFloat3(&this->local_rotation);
	XMVECTOR newRotation = XMVectorSet(pitch, yaw, roll, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentRotation, newRotation);
	XMStoreFloat3(&this->local_rotation, combinedRotation);
}

XMVECTOR AGameObject::getLocalRotation()
{
	return XMLoadFloat3(&this->local_rotation);
}

void AGameObject::setScale(float x, float y, float z)
{
	local_scale = XMFLOAT3(x, y, z);
}

void AGameObject::setScale(XMVECTOR vector)
{
	XMStoreFloat3(&this->local_scale, vector);
}

void AGameObject::scale(float scale)
{
	XMVECTOR currentScale = XMLoadFloat3(&this->local_scale);
	XMVECTOR newScale = XMVectorSet(scale, scale, scale, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentScale, newScale);
	XMStoreFloat3(&this->local_scale, combinedRotation);
}

XMVECTOR AGameObject::getLocalScale()
{
	return XMLoadFloat3(&this->local_scale);
}

XMMATRIX AGameObject::getWorldMatrix() const
{
	XMMATRIX matScale = XMMatrixScaling(local_scale.x, local_scale.y, local_scale.z);
	XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(local_rotation.x, local_rotation.y, local_rotation.z);
	XMMATRIX matTranslation = XMMatrixTranslation(local_position.x, local_position.y, local_position.z);

	return matScale * matRotation * matTranslation;
}

bool AGameObject::isActive()
{
	return this->active;
}

void AGameObject::setActive(bool value)
{
	this->active = value;
}
