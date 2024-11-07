#include "Quad.h"

Quad::Quad()
{
}

Quad::~Quad()
{
	this->release();
}

void Quad::initialize()
{
	this->active = true;

	this->vertices.clear();

	vertices.push_back({ XMFLOAT3(-1.f, -1.f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) }); // Bottom-left, red
	vertices.push_back({ XMFLOAT3(-1.f,  1.f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) }); // Top-left, green
	vertices.push_back({ XMFLOAT3(1.f,  1.f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) });  // Top-right, blue
	vertices.push_back({ XMFLOAT3(1.f, -1.f, 0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) });  // Bottom-right, yellow

	this->index_list = {
		0, 1, 2,
		2, 3, 0
	};
}

void Quad::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT vertexSize = sizeof(vertex);
	UINT vertexCount = static_cast<UINT>(vertices.size());

	indexBuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = static_cast<UINT>(index_list.size());
	indexBuffer->load(this->index_list.data(), size_index_list * sizeof(unsigned int));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(vsPath, vsEntry, &shader_byte_code, &size_shader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	vertexBuffer->load(vertices.data(), vertexSize, vertexCount, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(psPath, psEntry, &shader_byte_code, &size_shader);
	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant initialConstant;
	constantBuffer->load(&initialConstant, sizeof(constant));

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void Quad::update(float deltaTime)
{
}

void Quad::draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix, ID3D11ShaderResourceView* srv)
{
	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();
	constant cc;

	cc.m_world = this->getWorldMatrix();
	cc.m_view = view_matrix;
	cc.m_projection_matrix = projection_matrix;
	cc.screenSize = XMFLOAT4(width, height, 1.0f / width, 1.0f / height);
	cc.focalLength = 0.5f;  // Example: focal length (adjust as needed)
	cc.blurAmount = 10.0f;  // Amount of blur
	cc.maxBlurRadius = 0.01f;  // Max blur radius (controls blur strength)

	this->constantBuffer->update(context, &cc);

	context->setConstantBuffer(vertexShader, constantBuffer);
	context->setConstantBuffer(pixelShader, constantBuffer);

	context->setVertexShader(vertexShader);
	context->setPixelShader(pixelShader);

	context->setVertexBuffer(vertexBuffer);
	context->setIndexBuffer(this->indexBuffer);

	context->setPixelShaderResources(srv);

	context->drawIndexedTriangle(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Quad::release()
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

void Quad::setSize(float size)
{
	this->m_size = size;
}
