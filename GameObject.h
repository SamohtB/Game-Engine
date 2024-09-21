#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class GraphicsEngine;
class DeviceContext;

class GameObject
{

public:
	GameObject(vertex* data);
	~GameObject();
	
	virtual void draw() = 0;

protected:
	VertexBuffer* vertexBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

private:
	void createShaders(vertex* data);

};