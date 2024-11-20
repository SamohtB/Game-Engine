#include "MeshObject.h"
#include "Mesh.h"
#include "VertexMesh.h"

MeshObject::MeshObject(const wchar_t* mesh_file_path, const wchar_t* texture_file_path, const wchar_t* vs_path, const wchar_t* ps_path) : AGameObject()
{
    m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(mesh_file_path);
    m_texture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(texture_file_path);

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(vs_path, "vsmain", &shader_byte_code, &size_shader);
    m_vertex_shader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
    GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

    GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(ps_path, "psmain", &shader_byte_code, &size_shader);
    m_pixel_shader = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
    GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

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
    DeviceContextPtr context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();
    constant cc;

    cc.m_world = this->getWorldMatrix();
    cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
    cc.m_projection_matrix = SceneCameraHandler::getInstance()->getSceneCameraProjMatrix();

    this->m_constant_buffer->update(context, &cc);

    context->setConstantBuffer(m_vertex_shader, m_constant_buffer);
    context->setConstantBuffer(m_pixel_shader, m_constant_buffer);

    context->setVertexShader(m_vertex_shader);
    context->setPixelShader(m_pixel_shader);

    context->setTexture(m_pixel_shader, m_texture);

    context->setVertexBuffer(m_mesh->getVertexBuffer());
    context->setIndexBuffer(m_mesh->getIndexBuffer());

    context->drawIndexedTriangle(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}
