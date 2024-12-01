#include "Plane.h"
#include "ShaderLibrary.h"

Plane::Plane(String name, float width, float height) : Cube(name, width, height)
{
    this->setActive(true);
    this->setObjectType(AGameObject::PLANE);

    XMFLOAT3 vertex_data[4] =
    {
        { XMFLOAT3(-width, 0.0f, -height) },
        { XMFLOAT3(-width, 0.0f, height) },
        { XMFLOAT3(width, 0.0f, height) },
        { XMFLOAT3(width, 0.0f, -height) }
    };

    XMFLOAT2 texcoord_data[4] =
    {
        { XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT2(1.0f, 1.0f) },
    };

    vertex vertex_copy[4] =
    {
        { vertex_data[0], texcoord_data[1] },
        { vertex_data[1], texcoord_data[0] },
        { vertex_data[2], texcoord_data[2] },
        { vertex_data[3], texcoord_data[3] }
    };

    std::copy(std::begin(vertex_copy), std::end(vertex_copy), std::begin(m_vertex_list));

    unsigned int index_data[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    std::copy(std::begin(index_data), std::end(index_data), std::begin(m_index_list));

    ShaderNames shaderNames;
    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    UINT size_list = ARRAYSIZE(m_vertex_list);
    UINT size_index_list = ARRAYSIZE(m_index_list);

    ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(this->m_vertex_list, sizeof(vertex),
        size_list, shader_byte_code, (UINT)size_shader);

    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(this->m_index_list, size_index_list);

    constant initialConstant;
    m_constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&initialConstant, sizeof(constant));
}

Plane::~Plane() {}

