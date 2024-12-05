#include "Capsule.h"
#include "ShaderLibrary.h"
#include "GraphicsEngine.h"

Capsule::Capsule(String name, float radius, float height, XMFLOAT3 color) : AGameObject(name)
{
    this->setActive(true);
    this->setObjectType(AGameObject::CAPSULE);
    this->buildShape(radius, height, color);
}

Capsule::~Capsule()
{
}

void Capsule::update(float deltaTime)
{
}

void Capsule::draw(int radius, int height)
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

void Capsule::buildShape(float radius, float height, XMFLOAT3 color)
{
    std::vector<XMFLOAT3> positions;
    std::vector<XMFLOAT2> texcoords;
    std::vector<vertex> vertex_list;
    std::vector<UINT> index_list;

    const int numSlicesPlusOne = NUM_SLICES + 1;
    const int ringCount = NUM_STACKS + 1;
    const float stackHeight = height / NUM_STACKS;
    const float dTheta = 2.0f * XM_PI / NUM_SLICES;

    positions.reserve(ringCount * numSlicesPlusOne + 2 * (numSlicesPlusOne + 1) + 2 * (NUM_SLICES + 1));
    texcoords.reserve(positions.capacity());
    vertex_list.reserve(positions.capacity());
    index_list.reserve(NUM_STACKS * NUM_SLICES * 6 + NUM_SLICES * 6);

    /* main body */
    for (int i = 0; i < ringCount; ++i)
    {
        const float y = -0.5f * height + i * stackHeight;
        for (int j = 0; j <= NUM_SLICES; ++j)
        {
            const float c = radius * cos(j * dTheta);
            const float s = radius * sin(j * dTheta);
            positions.emplace_back(radius * c, y, radius * s);
            texcoords.emplace_back(static_cast<float>(j) / NUM_SLICES, 1.0f - static_cast<float>(i) / NUM_STACKS);
        }
    }

    /* main body indices */
    const int ringVertexCount = NUM_SLICES + 1;
    for (int i = 0; i < NUM_STACKS; ++i)
    {
        for (int j = 0; j < NUM_SLICES; ++j)
        {
            const int baseIndex = i * ringVertexCount + j;
            const int nextBaseIndex = (i + 1) * ringVertexCount + j;
            index_list.push_back(baseIndex);
            index_list.push_back(nextBaseIndex);
            index_list.push_back(nextBaseIndex + 1);
            index_list.push_back(baseIndex);
            index_list.push_back(nextBaseIndex + 1);
            index_list.push_back(baseIndex + 1);
        }
    }

    /* top cap */
    int baseIndex = static_cast<int>(positions.size());
    const int numStacksHemisphere = NUM_STACKS / 2;
    for (int i = 0; i <= numStacksHemisphere; ++i)
    {
        const float phi = XM_PIDIV2 * (static_cast<float>(i) / numStacksHemisphere);
        const float y = 0.5f * height + radius * sin(phi);
        const float r = radius * cos(phi);
        for (int j = 0; j <= NUM_SLICES; ++j)
        {
            const float theta = j * dTheta;
            const float x = r * cos(theta);
            const float z = r * sin(theta);
            positions.emplace_back(x, y, z);
            texcoords.emplace_back((x / radius) * 0.5f + 0.5f, (z / radius) * 0.5f + 0.5f);
        }
    }

    /* top cap indices */
    for (int i = 0; i < numStacksHemisphere; ++i)
    {
        for (int j = 0; j < NUM_SLICES; ++j)
        {
            const int baseIndex = ringCount * ringVertexCount + i * ringVertexCount + j;
            const int nextBaseIndex = baseIndex + ringVertexCount;
            index_list.push_back(baseIndex);
            index_list.push_back(nextBaseIndex);
            index_list.push_back(nextBaseIndex + 1);
            index_list.push_back(baseIndex);
            index_list.push_back(nextBaseIndex + 1);
            index_list.push_back(baseIndex + 1);
        }
    }

    /* bottom cap */
    baseIndex = static_cast<int>(positions.size());
    for (int i = 0; i <= numStacksHemisphere; ++i)
    {
        const float phi = XM_PIDIV2 * (static_cast<float>(i) / numStacksHemisphere); // From 0 to PI/2
        const float y = -0.5f * height - radius * sin(phi);
        const float r = radius * cos(phi);
        for (int j = 0; j <= NUM_SLICES; ++j)
        {
            const float theta = j * dTheta;
            const float x = r * cos(theta);
            const float z = r * sin(theta);
            positions.emplace_back(x, y, z);
            texcoords.emplace_back((x / radius) * 0.5f + 0.5f, (z / radius) * 0.5f + 0.5f);
        }
    }

    /* bottom cap indices */
    for (int i = 0; i < numStacksHemisphere; ++i)
    {
        for (int j = 0; j < NUM_SLICES; ++j)
        {
            const int baseIndex = static_cast<int>(positions.size()) - (numStacksHemisphere + 1) * ringVertexCount + i * ringVertexCount + j;
            const int nextBaseIndex = baseIndex + ringVertexCount;
            index_list.push_back(baseIndex);
            index_list.push_back(nextBaseIndex + 1);
            index_list.push_back(nextBaseIndex);
            index_list.push_back(baseIndex);
            index_list.push_back(baseIndex + 1);
            index_list.push_back(nextBaseIndex + 1);
        }
    }

    for (size_t i = 0; i < positions.size(); ++i)
    {
        vertex_list.emplace_back(positions[i], texcoords[i], color);
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
