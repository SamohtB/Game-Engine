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
        m_mesh_manager = new MeshManager();
    }
    catch (...)
    {
        throw std::exception("MeshManager not created successfully");
    }
}

GraphicsEngine::~GraphicsEngine() 
{
    delete m_mesh_manager;
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

MeshManager* GraphicsEngine::getMeshManager()
{
    return m_mesh_manager;
}
