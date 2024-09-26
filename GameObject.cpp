#include "GameObject.h"


GameObject::GameObject(vertex* data)
{
	createShaders(data);
}

GameObject::~GameObject() {}

void GameObject::release()
{
	this->vertexBuffer->release();
	this->vertexShader->release();
	this->pixelShader->release();
}

void GameObject::createShaders(vertex* data)
{
	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = sizeof(data);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertexShader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	vertexBuffer->load(data, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	pixelShader = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	constant cc;
	cc.m_angle = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));

	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObject::update(DeviceContext* context, void* buffer)
{
	constantBuffer->update(context, buffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
}
