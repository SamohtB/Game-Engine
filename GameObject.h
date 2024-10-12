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

struct vec4
{
	float x, y, z, w;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

struct alignas(16) constant
{
	vec4 directionalLightDir;
	vec4 directionalLightColor;
	vec4 directionalLightAmbientColor;
	vec4 lightParameters;
	vec4 cameraPos;
};

class GraphicsEngine;
class DeviceContext;

class GameObject
{

public:
	GameObject();
	~GameObject();
	
	void updateConstantBuffer(void* buffer);
	virtual void update(float deltaTime) {};
	virtual void draw();
	void release();

	void setTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);

protected:
	std::vector<vertex> m_vertices;
	D3D11_PRIMITIVE_TOPOLOGY m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	vec3 m_position;

	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
};