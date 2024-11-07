#pragma once
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

class GraphicsEngine;
class DeviceContext;

class GameObject
{

public:
	GameObject();
	~GameObject();
	
	virtual void initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix) = 0;

	bool isActive();
	void setActive(bool value);

	void setPosition(float x, float y, float z);
	void setPosition(XMVECTOR vector);
	XMVECTOR getLocalPosition();

	void setRotation(float pitch, float yaw, float roll);
	void setRotation(XMVECTOR vector);
	void rotate(float pitch, float yaw, float roll);
	XMVECTOR getLocalRotation();

	void setScale(float x, float y, float z);
	void setScale(XMVECTOR vector);
	void scale(float scale);
	XMVECTOR getLocalScale();

	XMMATRIX getWorldMatrix() const;

	struct vertex
	{
		XMFLOAT3 position;
		XMFLOAT3 color;
	};

	struct alignas(16) constant
	{
		XMMATRIX m_world;
		XMMATRIX m_view;
		XMMATRIX m_projection_matrix;
	};

protected:
	XMFLOAT3 local_position;
	XMFLOAT3 local_rotation;
	XMFLOAT3 local_scale;
	XMMATRIX local_matrix;

	bool active = false;
};