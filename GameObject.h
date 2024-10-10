#pragma once
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Matrix4x4.h"

#include <vector>

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

struct alignas(16) constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection_matrix;
	float elapsedTime;
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