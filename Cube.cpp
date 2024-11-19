#include "Cube.h"

Cube::Cube(float size) 
{
    this->active = true;

    XMFLOAT3 vertex_data[8] =
    {
        { XMFLOAT3(-size, -size, -size) },
        { XMFLOAT3(-size,  size, -size) },
        { XMFLOAT3(size, size, -size) },
        { XMFLOAT3(size, -size, -size) },
        { XMFLOAT3(size, -size, size) },
        { XMFLOAT3(size, size, size) },
        { XMFLOAT3(-size, size, size) },
        { XMFLOAT3(-size, -size, size) }
    };

    XMFLOAT2 texcoord_data[4] =
    {
        { XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT2(1.0f, 1.0f) },
    };

    vertex vertex_copy[24] =
    {
        { vertex_data[0], texcoord_data[1] },
        { vertex_data[1], texcoord_data[0] },
        { vertex_data[2], texcoord_data[2] },
        { vertex_data[3], texcoord_data[3] },

        { vertex_data[4], texcoord_data[1] },
        { vertex_data[5], texcoord_data[0] },
        { vertex_data[6], texcoord_data[2] },
        { vertex_data[7], texcoord_data[3] },

        { vertex_data[1], texcoord_data[1] },
        { vertex_data[6], texcoord_data[0] },
        { vertex_data[5], texcoord_data[2] },
        { vertex_data[2], texcoord_data[3] },

        { vertex_data[7], texcoord_data[1] },
        { vertex_data[0], texcoord_data[0] },
        { vertex_data[3], texcoord_data[2] },
        { vertex_data[4], texcoord_data[3] },

        { vertex_data[3], texcoord_data[1] },
        { vertex_data[2], texcoord_data[0] },
        { vertex_data[5], texcoord_data[2] },
        { vertex_data[4], texcoord_data[3] },

        { vertex_data[7], texcoord_data[1] },
        { vertex_data[6], texcoord_data[0] },
        { vertex_data[1], texcoord_data[2] },
        { vertex_data[0], texcoord_data[3] },
    };

    std::copy(std::begin(vertex_copy), std::end(vertex_copy), std::begin(m_vertex_list));

    unsigned int index_data[] =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };

    std::copy(std::begin(index_data), std::end(index_data), std::begin(m_index_list));
}

Cube::~Cube() {}

void Cube::loadTexture(const wchar_t* texture_path)
{
    m_texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(texture_path);
}

void Cube::loadShaders(const wchar_t* vs_path, const char* vs_entry, const wchar_t* ps_path, const char* ps_entry)
{
    UINT size_list = ARRAYSIZE(m_vertex_list);
    UINT size_index_list = ARRAYSIZE(m_index_list);

    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(this->m_index_list, size_index_list);

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(vs_path, vs_entry, &shader_byte_code, &size_shader);

    m_vertex_shader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(m_vertex_list, sizeof(vertex), size_list, shader_byte_code, static_cast<UINT>(size_shader));

    GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

    GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(ps_path, ps_entry, &shader_byte_code, &size_shader);

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
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = view_matrix;
    cc.m_projection_matrix = projection_matrix;

    this->m_constant_buffer->update(context, &cc);

    context->setConstantBuffer(m_vertex_shader, m_constant_buffer);
    context->setConstantBuffer(m_pixel_shader, m_constant_buffer);

    context->setVertexShader(m_vertex_shader);
    context->setPixelShader(m_pixel_shader);

    context->setTexture(m_pixel_shader, m_texture);

    context->setVertexBuffer(m_vertex_buffer);
    context->setIndexBuffer(this->m_index_buffer);

    context->drawIndexedTriangle(this->m_index_buffer->getSizeIndexList(), 0, 0);
}
