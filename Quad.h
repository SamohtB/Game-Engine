#pragma once
#include "GameObject.h"
#include "GraphicsEngine.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};


class Quad : public GameObject
{
public:
	Quad(vertex pos) 
	{
		this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
		UINT size_list = ARRAYSIZE(pos);

		GraphicsEngine::get()->createShaders();

		void* shader_byte_code = nullptr;
		UINT size_shader = 0;
		GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

		this->vertexBuffer->load(pos, sizeof(vertex), size_list, shader_byte_code, size_shader);
	}

	void draw(ID3D11DeviceContext* m_device_context) override;
};

