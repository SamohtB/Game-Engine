#include "GameObject.h"


GameObject::GameObject() 
{

}

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
	if (indexBuffer)
	{
		indexBuffer->release();
		indexBuffer = nullptr;
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

void GameObject::initialize(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT vertexSize = sizeof(vertex);
	UINT vertexCount = static_cast<UINT>(vertices.size());

	indexBuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = static_cast<UINT>(index_list.size());
	indexBuffer->load(this->index_list.data(), size_index_list *sizeof(unsigned int));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(vsPath, vsEntry, &shader_byte_code, &size_shader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	vertexBuffer->load(vertices.data(), vertexSize, vertexCount, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->compilePixelShader(psPath, psEntry, &shader_byte_code, &size_shader);
	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant initialConstant;
	constantBuffer->load(&initialConstant, sizeof(constant));

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void GameObject::update(DeviceContext* context, void* buffer)
{
	constantBuffer->update(context, buffer);
}

void GameObject::draw()
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	context->setConstantBuffer(vertexShader, constantBuffer);
	context->setConstantBuffer(pixelShader, constantBuffer);

	context->setVertexShader(vertexShader);
	context->setPixelShader(pixelShader);

	context->setVertexBuffer(vertexBuffer);
	context->setIndexBuffer(indexBuffer);

	context->draw(this->indexBuffer->getSizeIndexList(), 0, 0, m_topology);
}

void GameObject::setTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_topology = topology;
}
