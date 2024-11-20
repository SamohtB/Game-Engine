#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine() 
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) 
	{
		throw std::exception("RenderSystem not created successfully");
	}

    try
    {
        m_texture_manager = new TextureManager();
    }
    catch (...)
    {
        throw std::exception("TextureManager not created successfully");
    }

    try
    {
        m_mesh_manager = new MeshManager();
    }
    catch (...)
    {
        throw std::exception("MeshManager not created successfully");
    }

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
    ::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
    m_mesh_layout_size = size_shader;
    m_render_system->releaseCompiledShader();
}

GraphicsEngine::~GraphicsEngine() 
{
    delete m_mesh_manager;
    delete m_texture_manager;
	delete m_render_system;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	try
	{
		sharedInstance = new GraphicsEngine();
	}
	catch (...)
	{
		throw std::exception("GraphicsEngine not created successfully");
	}
}

void GraphicsEngine::destroy()
{
	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
    return m_texture_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
    return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
    *byte_code = m_mesh_layout_byte_code;
    *size = m_mesh_layout_size;
}
