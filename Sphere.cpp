#include "Sphere.h"
#include "ShaderLibrary.h"
#include "GraphicsEngine.h"

Sphere::Sphere(String name, float radius, XMFLOAT3 color) : AGameObject(name)
{
    this->setActive(true);
    this->setObjectType(AGameObject::SPHERE);
    this->buildShape(radius, color);
}

Sphere::~Sphere()
{
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(int width, int height)
{
    ShaderNames shaderNames;
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    TexturePtr texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
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

void Sphere::buildShape(float radius, XMFLOAT3 color)
{
    std::vector<XMFLOAT3> positions;
    std::vector<XMFLOAT2> texcoords;
    std::vector<vertex> vertex_list;
    std::vector<UINT> index_list;

    float x, y, z, xy;
    float s, t;

    float sectorStep = 2 * XM_PI / NUM_SECTORS;
    float stackStep = XM_PI / NUM_RINGS;
    float sectorAngle, stackAngle;

    /* calculate vertices */
    for (int i = 0; i <= NUM_RINGS; ++i)
    {
        stackAngle = XM_PI / 2 - i * stackStep;        
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= NUM_SECTORS; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            positions.push_back(XMFLOAT3(x, y, z));

            s = (float)j / NUM_SECTORS;
            t = (float)i / NUM_RINGS;
            texcoords.push_back(XMFLOAT2(s, t));
        }
    }
    
    for (size_t i = 0; i < positions.size(); ++i)
    {
        vertex_list.push_back({ positions[i], texcoords[i], color });
    }

    /* calculate indices */
    int k1, k2;
    for (int i = 0; i < NUM_RINGS; ++i)
    {
        k1 = i * (NUM_SECTORS + 1);
        k2 = k1 + NUM_SECTORS + 1;

        for (int j = 0; j < NUM_SECTORS; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                index_list.push_back(k1);
                index_list.push_back(k2);
                index_list.push_back(k1 + 1);
            }

            if (i != (NUM_RINGS - 1))
            {
                index_list.push_back(k1 + 1);
                index_list.push_back(k2);
                index_list.push_back(k2 + 1);
            }
        }
    }

    ShaderNames shaderNames;
    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    UINT size_list = static_cast<UINT>(vertex_list.size());
    UINT size_index_list = static_cast<UINT>(index_list.size());

    ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertex_list.data(), sizeof(vertex),
        size_list, shader_byte_code, (UINT)size_shader);


    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list.data(), size_index_list);

    constant initialConstant;
    m_constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&initialConstant, sizeof(constant));
}
