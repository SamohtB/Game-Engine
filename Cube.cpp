#include "Cube.h"
#include "ShaderLibrary.h"
#include "GraphicsEngine.h"

Cube::Cube(String name, float width, float height, XMFLOAT3 color) : AGameObject(name)
{
    this->setActive(true);
    this->setObjectType(AGameObject::CUBE);
    this->buildShape(width, height, color);
    this->setTextureType(TextureManager::BRICK);
}

Cube::~Cube() {}

void Cube::update(float deltaTime)
{

}

void Cube::draw(int width, int height)
{
    ShaderNames shaderNames;
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    TexturePtr texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(this->getTextureType());
    constant cc;

    XMVECTOR position = this->getLocalPosition();
    XMVECTOR rotation = this->getLocalRotation();
    XMVECTOR scale = this->getLocalScale();

    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(position);
    XMMATRIX scaleMatrix = XMMatrixScalingFromVector(scale);

    XMMATRIX rotationMatrixX = XMMatrixRotationX(XMConvertToRadians(XMVectorGetX(rotation)));
    XMMATRIX rotationMatrixY = XMMatrixRotationY(XMConvertToRadians(XMVectorGetY(rotation)));
    XMMATRIX rotationMatrixZ = XMMatrixRotationZ(XMConvertToRadians(XMVectorGetZ(rotation)));

    XMMATRIX rotationMatrix = XMMatrixMultiply(rotationMatrixX, XMMatrixMultiply(rotationMatrixY, rotationMatrixZ));
    XMMATRIX worldMatrix = XMMatrixMultiply(scaleMatrix, XMMatrixMultiply(rotationMatrix, translationMatrix));

    cc.m_world = worldMatrix;
    cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
    cc.m_projection_matrix = SceneCameraHandler::getInstance()->getSceneCameraProjMatrix();

    this->m_constant_buffer->update(context, &cc);

    context->setConstantBuffer(m_constant_buffer);

    context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME));
    context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

    context->setTexture(texture);

    context->setVertexBuffer(m_vertex_buffer);
    context->setIndexBuffer(this->m_index_buffer);

    context->drawIndexedTriangle(this->m_index_buffer->getSizeIndexList(), 0, 0);
}

void Cube::buildShape(float width, float height, XMFLOAT3 color)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    XMFLOAT3 vertex_data[8] =
    {
        { XMFLOAT3(-halfWidth, -halfHeight, -halfWidth) },
        { XMFLOAT3(-halfWidth,  halfHeight, -halfWidth) },
        { XMFLOAT3(halfWidth,  halfHeight, -halfWidth) },
        { XMFLOAT3(halfWidth, -halfHeight, -halfWidth) },
        { XMFLOAT3(halfWidth, -halfHeight,  halfWidth) },
        { XMFLOAT3(halfWidth,  halfHeight,  halfWidth) },
        { XMFLOAT3(-halfWidth,  halfHeight,  halfWidth) },
        { XMFLOAT3(-halfWidth, -halfHeight,  halfWidth) }
    };


    XMFLOAT2 texcoord_data[4] =
    {
        { XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT2(1.0f, 1.0f) },
    };

    vertex vertex_list[24] =
    {
        { vertex_data[0], texcoord_data[1], color },
        { vertex_data[1], texcoord_data[0], color },
        { vertex_data[2], texcoord_data[2], color },
        { vertex_data[3], texcoord_data[3], color },

        { vertex_data[4], texcoord_data[1], color },
        { vertex_data[5], texcoord_data[0], color },
        { vertex_data[6], texcoord_data[2], color },
        { vertex_data[7], texcoord_data[3], color },

        { vertex_data[1], texcoord_data[1], color },
        { vertex_data[6], texcoord_data[0], color },
        { vertex_data[5], texcoord_data[2], color },
        { vertex_data[2], texcoord_data[3], color },

        { vertex_data[7], texcoord_data[1], color },
        { vertex_data[0], texcoord_data[0], color },
        { vertex_data[3], texcoord_data[2], color },
        { vertex_data[4], texcoord_data[3], color },

        { vertex_data[3], texcoord_data[1], color },
        { vertex_data[2], texcoord_data[0], color },
        { vertex_data[5], texcoord_data[2], color },
        { vertex_data[4], texcoord_data[3], color },

        { vertex_data[7], texcoord_data[1], color },
        { vertex_data[6], texcoord_data[0], color },
        { vertex_data[1], texcoord_data[2], color },
        { vertex_data[0], texcoord_data[3], color },
    };


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

    ShaderNames shaderNames;
    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    UINT size_list = ARRAYSIZE(vertex_list);
    UINT size_index_list = ARRAYSIZE(index_data);

    ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex),
        size_list, shader_byte_code, (UINT)size_shader);


    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_data, size_index_list);

    constant initialConstant;
    m_constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&initialConstant, sizeof(constant));
}
