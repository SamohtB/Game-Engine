#pragma once
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

struct alignas(16) constant
{
	float deltaTime;
};

class GraphicsEngine;
class DeviceContext;

class GameObject
{

public:
	GameObject();
	~GameObject();
	
	virtual void initialize(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);
	virtual void update(DeviceContext* context, void* buffer);
	virtual void draw();
	void release();

	void setTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
protected:
	std::vector<vertex> vertices;
	D3D11_PRIMITIVE_TOPOLOGY m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
};