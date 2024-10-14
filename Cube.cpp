#include "Cube.h"

Cube::Cube()
{
    this->index_list =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        1, 6, 5,
        5, 2, 1,
        7, 0, 3,
        3, 4, 7,
        3, 2, 5,
        5, 4, 3,
        7, 6, 1,
        1, 0, 7,
    };
}

Cube::~Cube()
{
    this->release();
}

void Cube::initialize()
{
    this->active = true;

    this->vertices =
    {
        { XMFLOAT3(-m_size, -m_size, -m_size), XMFLOAT3(0.8f, 0.5f, 0.5f) }, 
        { XMFLOAT3(-m_size,  m_size, -m_size), XMFLOAT3(0.5f, 0.8f, 0.5f) }, 
        { XMFLOAT3(m_size,  m_size, -m_size), XMFLOAT3(0.5f, 0.5f, 0.8f) }, 
        { XMFLOAT3(m_size, -m_size, -m_size), XMFLOAT3(0.8f, 0.8f, 0.5f) }, 
        { XMFLOAT3(m_size, -m_size,  m_size), XMFLOAT3(0.8f, 0.5f, 0.8f) }, 
        { XMFLOAT3(m_size,  m_size,  m_size), XMFLOAT3(0.5f, 0.8f, 0.8f) }, 
        { XMFLOAT3(-m_size,  m_size,  m_size), XMFLOAT3(0.5f, 0.5f, 0.5f) }, 
        { XMFLOAT3(-m_size, -m_size,  m_size), XMFLOAT3(0.8f, 0.8f, 0.8f) }
    };
}

void Cube::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
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

void Cube::update(float deltaTime)
{
    this->m_ticks += deltaTime;

    XMVECTOR targetRotation = { m_ticks * m_speed, m_ticks * m_speed, m_ticks * m_speed };
    XMVECTOR currentRotation = getLocalRotation();

    float lerpFactor = deltaTime;
    currentRotation = XMVectorLerp(currentRotation, targetRotation, lerpFactor);

    setRotation(currentRotation);
}

void Cube::draw(int width, int height)
{
    DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = XMMatrixIdentity();
    cc.m_projection_matrix = XMMatrixOrthographicLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

    this->constantBuffer->update(context, &cc);

    context->setConstantBuffer(vertexShader, constantBuffer);
    context->setConstantBuffer(pixelShader, constantBuffer);

    context->setVertexShader(vertexShader);
    context->setPixelShader(pixelShader);

    context->setVertexBuffer(vertexBuffer);
    context->setIndexBuffer(this->indexBuffer);

    context->drawIndexedTriangle(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Cube::setSize(float size)
{
    this->m_size = size;
}

void Cube::setSpeed(float speed)
{
    this->m_speed = speed;
}

void Cube::release()
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
