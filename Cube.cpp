#include "Cube.h"

Cube::Cube(float size) 
{
    this->active = true;

    vertex vertex_data[] =
    {
        { DirectX::XMFLOAT3(-size, -size, -size), DirectX::XMFLOAT3(0.3f, 0.5f, 0.5f) },
        { DirectX::XMFLOAT3(-size,  size, -size), DirectX::XMFLOAT3(0.1f, 0.4f, 0.5f) },
        { DirectX::XMFLOAT3(size, size, -size), DirectX::XMFLOAT3(0.8f, 0.2f, 0.5f) },
        { DirectX::XMFLOAT3(size, -size, -size), DirectX::XMFLOAT3(0.8f, 0.1f, 0.5f) },
        { DirectX::XMFLOAT3(size, -size, size), DirectX::XMFLOAT3(0.8f, 0.7f, 0.5f) },
        { DirectX::XMFLOAT3(size, size, size), DirectX::XMFLOAT3(0.8f, 0.8f, 0.5f) },
        { DirectX::XMFLOAT3(-size, size, size), DirectX::XMFLOAT3(0.8f, 0.9f, 0.5f) },
        { DirectX::XMFLOAT3(-size, -size, size), DirectX::XMFLOAT3(0.8f, 0.5f, 0.4f) }
    };

    std::copy(std::begin(vertex_data), std::end(vertex_data), std::begin(m_vertex_list));

    unsigned int index_data[] =
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
        1, 0, 7
    };

    std::copy(std::begin(index_data), std::end(index_data), std::begin(m_index_list));
}

Cube::~Cube() 
{
    if (m_vertex_buffer) delete m_vertex_buffer;
    if (m_constant_buffer) delete m_constant_buffer;
    if (m_index_buffer) delete m_index_buffer;
    if (m_vertex_shader) delete m_vertex_shader;
    if (m_pixel_shader) delete m_pixel_shader;
}

void Cube::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
    UINT size_list = ARRAYSIZE(m_vertex_list);
    UINT size_index_list = ARRAYSIZE(m_index_list);

    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(this->m_index_list, size_index_list);

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(vsPath, vsEntry, &shader_byte_code, &size_shader);

    m_vertex_shader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(m_vertex_list, sizeof(vertex), size_list, shader_byte_code, static_cast<UINT>(size_shader));

    GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

    GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(psPath, psEntry, &shader_byte_code, &size_shader);

    m_pixel_shader = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

    GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

    constant initialConstant;
    m_constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&initialConstant, sizeof(constant));
}

void Cube::update(float deltaTime)
{
    this->m_ticks += deltaTime;
}

void Cube::draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
    DeviceContext* context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = view_matrix;
    cc.m_projection_matrix = projection_matrix;

    this->m_constant_buffer->update(context, &cc);

    context->setConstantBuffer(m_vertex_shader, m_constant_buffer);
    context->setConstantBuffer(m_pixel_shader, m_constant_buffer);

    context->setVertexShader(m_vertex_shader);
    context->setPixelShader(m_pixel_shader);

    context->setVertexBuffer(m_vertex_buffer);
    context->setIndexBuffer(this->m_index_buffer);

    context->drawIndexedTriangle(this->m_index_buffer->getSizeIndexList(), 0, 0);
}
