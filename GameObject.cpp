#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() 
{
	release();
}

void GameObject::release()
{
	if (vertexBuffer)
	{
		vertexBuffer->release();
		vertexBuffer = nullptr;
	}
	if (constantBuffer)
	{
		constantBuffer->release();
		constantBuffer = nullptr;
	}
	if (vertexShader)
	{
		vertexShader->release();
		vertexShader = nullptr;
	}
	if (pixelShader)
	{
		pixelShader->release();
		pixelShader = nullptr;
	}
}

void GameObject::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT vertexSize = sizeof(vertex);
	UINT vertexCount = static_cast<UINT>(this->m_vertices.size());

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(vsPath, vsEntry, &shader_byte_code, &size_shader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	vertexBuffer->load(this->m_vertices.data(), vertexSize, vertexCount, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->compilePixelShader(psPath, psEntry, &shader_byte_code, &size_shader);
	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);	

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant initialConstant;
	constantBuffer->load(&initialConstant, sizeof(constant));

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void GameObject::updateConstantBuffer(void* buffer)
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();
	constantBuffer->update(context, buffer);
}

void GameObject::setTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_topology = topology;
}

void GameObject::draw()
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	context->setConstantBuffer(vertexShader, constantBuffer);
	context->setConstantBuffer(pixelShader, constantBuffer);

	context->setVertexShader(vertexShader);
	context->setPixelShader(pixelShader);

	context->setVertexBuffer(vertexBuffer);

	context->draw(this->vertexBuffer->getSizeVertexList(), 0, this->m_topology);
}
