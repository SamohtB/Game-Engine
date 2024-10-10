#pragma once
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

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
	float elapsedTime;
};

class GraphicsEngine;
class DeviceContext;

class GameObject
{

public:
	GameObject();
	~GameObject();
	
	virtual void update(float deltaTime);
	virtual void draw();
	void release();

	void setWindowParameters(float width, float height);
	void setTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);

	bool isActive();
	void setActive(bool value);

	void setPosition(float x, float y, float z);
	void setRotation(float pitch, float yaw, float roll);
	void setScale(float x, float y, float z);
	XMMATRIX getWorldMatrix() const;

protected:
	std::vector<vertex> vertices;

	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	float windowWidth = 0;
	float windowHeight = 0;
	float nearPlane = -4.0f;
	float farPlane = 4.0f;

	bool active = false;

	D3D11_PRIMITIVE_TOPOLOGY m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

private:
	void updateConstantBuffer(DeviceContext* context, void* buffer);
};