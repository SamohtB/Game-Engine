#include "Cube.h"

Cube::Cube() {}

Cube::~Cube()
{
    this->release();
}

void Cube::initialize()
{
    this->active = true;

    this->vertices.clear();

    this->vertices.push_back({ XMFLOAT3(-m_size, -m_size, -m_size), XMFLOAT3(0.3f, 0.5f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(-m_size,  m_size, -m_size), XMFLOAT3(0.1f, 0.4f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(m_size, m_size, -m_size), XMFLOAT3(0.8f, 0.2f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(m_size, -m_size, -m_size), XMFLOAT3(0.8f, 0.1f, 0.5f) });

    this->vertices.push_back({ XMFLOAT3(m_size, -m_size, m_size), XMFLOAT3(0.8f, 0.7f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(m_size, m_size, m_size), XMFLOAT3(0.8f, 0.8f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(-m_size, m_size, m_size), XMFLOAT3(0.8f, 0.9f, 0.5f) });
    this->vertices.push_back({ XMFLOAT3(-m_size, -m_size, m_size), XMFLOAT3(0.8f, 0.5f, 0.4f) });

    this->index_list = {
        //FRONT SIDE
        0,1,2,  //FIRST TRIANGLE
        2,3,0,  //SECOND TRIANGLE
        //BACK SIDE
        4,5,6,
        6,7,4,
        //TOP SIDE
        1,6,5,
        5,2,1,
        //BOTTOM SIDE
        7,0,3,
        3,4,7,
        //RIGHT SIDE
        3,2,5,
        5,4,3,
        //LEFT SIDE
        7,6,1,
        1,0,7
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
}

void Cube::draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
    DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = view_matrix;
    cc.m_projection_matrix = projection_matrix;
    cc.focalPlane = 0.5f;
    cc.focusRange = 0.1f;
    cc.blurRange = 0.2f; 

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
