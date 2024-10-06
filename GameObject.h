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
	
	virtual void update(DeviceContext* context, void* buffer);
	virtual void draw();
	void release();

	void setShaders(vertex* data, constant* cc);
protected:
	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
};