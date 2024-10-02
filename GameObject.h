#pragma once
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

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
	
	virtual void update(DeviceContext* context, void* buffer);
	virtual void draw();

	void createShaders(vertex* data, constant* cc);
	void release();

protected:
	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
};