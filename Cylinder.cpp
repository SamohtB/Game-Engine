#include "Cylinder.h"
#include "ShaderLibrary.h"

Cylinder::Cylinder(String name, float width, float height) : AGameObject(name)
{
    this->setActive(true);
    this->setObjectType(AGameObject::PLANE);
    this->buildShape(width, height);
}

Cylinder::~Cylinder()
{
}

void Cylinder::update(float deltaTime)
{
}

void Cylinder::draw(int width, int height)
{
    ShaderNames shaderNames;
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    TexturePtr texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
    constant cc;

    XMVECTOR position = this->getLocalPosition();
    XMVECTOR rotation = this->getLocalRotation();
    XMVECTOR scale = this->getLocalScale();

    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(position);
    XMMATRIX scaleMatrix = XMMatrixScalingFromVector(scale);

    XMMATRIX rotationMatrixX = XMMatrixRotationX(XMVectorGetX(rotation));
    XMMATRIX rotationMatrixY = XMMatrixRotationY(XMVectorGetY(rotation));
    XMMATRIX rotationMatrixZ = XMMatrixRotationZ(XMVectorGetZ(rotation));

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

void Cylinder::buildShape(float radius, float height)
{
    std::vector<XMFLOAT3> positions;
    std::vector<XMFLOAT2> texcoords;
    std::vector<vertex> vertex_list;
    std::vector<UINT> index_list;

    const int numSlicesPlusOne = NUM_SLICES + 1;
    const int ringCount = NUM_STACKS + 1;
    const float stackHeight = height / NUM_STACKS;
    const float dTheta = 2.0f * XM_PI / NUM_SLICES;

    positions.reserve(ringCount * numSlicesPlusOne + 2 * (numSlicesPlusOne + 1) + 2);
    texcoords.reserve(ringCount * numSlicesPlusOne + 2 * (numSlicesPlusOne + 1) + 2);
    vertex_list.reserve(positions.capacity());
    index_list.reserve(NUM_STACKS * NUM_SLICES * 6 + NUM_SLICES * 6);

    /* main body */
    for (int i = 0; i < ringCount; ++i)
    {
        const float y = -0.5f * height + i * stackHeight;
        for (int j = 0; j <= NUM_SLICES; ++j)
        {
            const float c = cos(j * dTheta);
            const float s = sin(j * dTheta);
            positions.emplace_back(radius * c, y, radius * s);
            texcoords.emplace_back(static_cast<float>(j) / NUM_SLICES, 1.0f - static_cast<float>(i) / NUM_STACKS);
        }
    }

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
    const float topY = 0.5f * height;

    for (int i = 0; i <= NUM_SLICES; ++i)
    {
        const float x = radius * cos(i * dTheta);
        const float z = radius * sin(i * dTheta);
        positions.emplace_back(x, topY, z);
        texcoords.emplace_back(x / height + 0.5f, z / height + 0.5f);
    }

    /* top cap center */
    positions.emplace_back(0, topY, 0);
    texcoords.emplace_back(0.5f, 0.5f);

    int centerIndex = static_cast<int>(positions.size()) - 1;
    for (int i = 0; i < NUM_SLICES; ++i)
    {
        index_list.push_back(centerIndex);
        index_list.push_back(baseIndex + i + 1);
        index_list.push_back(baseIndex + i);
    }

    /* bottom cap */
    baseIndex = static_cast<int>(positions.size());
    const float bottomY = -0.5f * height;

    for (int i = 0; i <= NUM_SLICES; ++i)
    {
        const float x = radius * cos(i * dTheta);
        const float z = radius * sin(i * dTheta);
        positions.emplace_back(x, bottomY, z);
        texcoords.emplace_back(x / height + 0.5f, z / height + 0.5f);
    }

    /* bottom cap center */
    positions.emplace_back(0, bottomY, 0);
    texcoords.emplace_back(0.5f, 0.5f);

    centerIndex = static_cast<int>(positions.size()) - 1;
    for (int i = 0; i < NUM_SLICES; ++i)
    {
        index_list.push_back(centerIndex);
        index_list.push_back(baseIndex + i);
        index_list.push_back(baseIndex + i + 1);
    }

    for (size_t i = 0; i < positions.size(); ++i)
    {
        vertex_list.emplace_back(positions[i], texcoords[i]);
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
