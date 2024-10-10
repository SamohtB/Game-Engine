#include "GameObject.h"


GameObject::GameObject() 
{
	this->position = XMFLOAT3(0, 0, 0);
	this->rotation = XMFLOAT3(0, 0, 0);
	this->scale = XMFLOAT3(1, 1, 1);
}

GameObject::~GameObject() 
{
	release();
}

void GameObject::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT vertexSize = sizeof(vertex);
	UINT vertexCount = static_cast<UINT>(vertices.size());
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

void GameObject::updateConstantBuffer(DeviceContext* context, void* buffer)
{
	constantBuffer->update(context, buffer);
}

void GameObject::update(float deltaTime)
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	XMMATRIX worldMatrix = getWorldMatrix();
	XMMATRIX viewMatrix = XMMatrixIdentity();
	XMMATRIX projectionMatrix = XMMatrixOrthographicLH(this->windowWidth, this->windowHeight, nearPlane, farPlane);

	constant cbData;
	cbData.m_world = worldMatrix;
	cbData.m_view = viewMatrix;
	cbData.m_projection_matrix = projectionMatrix;
	cbData.elapsedTime = deltaTime;

	updateConstantBuffer(context, &cbData);
}

void GameObject::draw()
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	context->setConstantBuffer(vertexShader, constantBuffer);
	context->setConstantBuffer(pixelShader, constantBuffer);

	context->setVertexShader(vertexShader);
	context->setPixelShader(pixelShader);

	context->setVertexBuffer(vertexBuffer);

	context->draw(this->vertexBuffer->getSizeVertexList(), 0, m_topology);
}

void GameObject::setTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_topology = topology;
}

void GameObject::setPosition(float x, float y, float z)
{
	position = XMFLOAT3(x, y, z);
}

void GameObject::setRotation(float pitch, float yaw, float roll)
{
	rotation = XMFLOAT3(pitch, yaw, roll);
}

void GameObject::setScale(float x, float y, float z)
{
	scale = XMFLOAT3(x, y, z);
}

XMMATRIX GameObject::getWorldMatrix() const
{
	XMMATRIX matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX matTranslation = XMMatrixTranslation(position.x, position.y, position.z);

	return matScale * matRotation * matTranslation;
}

void GameObject::setWindowParameters(float width, float height)
{
	this->windowWidth = width;
	this->windowHeight = height;
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
