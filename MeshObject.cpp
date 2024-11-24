#include "MeshObject.h"
#include "Mesh.h"
#include "VertexMesh.h"
#include "RenderSystem.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

MeshObject::MeshObject(const wchar_t* mesh_file_path) : AGameObject()
{
    m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(mesh_file_path);

    constant initialConstant;
    m_constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&initialConstant, sizeof(constant));
}

MeshObject::~MeshObject()
{
}

void MeshObject::update(float deltaTime)
{
}

void MeshObject::draw(int width, int height)
{
    ShaderNames shaderNames;
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    TexturePtr texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
    cc.m_projection_matrix = SceneCameraHandler::getInstance()->getSceneCameraProjMatrix();

    this->m_constant_buffer->update(context, &cc);

    context->setConstantBuffer(m_constant_buffer);

    context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME));
    context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

    context->setTexture(texture);

    context->setVertexBuffer(m_mesh->getVertexBuffer());
    context->setIndexBuffer(m_mesh->getIndexBuffer());

    context->drawIndexedTriangle(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}
