#include "GameObject.h"


GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::release()
{
	this->vertexBuffer->release();
	this->vertexShader->release();
	this->pixelShader->release();
}

void GameObject::createShaders(vertex* data, constant* cc)
{
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = sizeof(data);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	vertexBuffer->load(data, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);	

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(cc, sizeof(constant));

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void GameObject::update(DeviceContext* context, void* buffer)
{
	constantBuffer->update(context, buffer);
}

void GameObject::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
}
