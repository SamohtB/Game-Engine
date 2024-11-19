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
}

GraphicsEngine::~GraphicsEngine() 
{
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
