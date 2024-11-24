#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include <sstream>

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;

ShaderLibrary* ShaderLibrary::getInstance()
{
    return sharedInstance;
}

void ShaderLibrary::initialize()
{
    sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
    delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertex_shader_name, void** shader_byte_code, size_t* size_shader)
{
    GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(vertex_shader_name.c_str(), "vsmain", shader_byte_code, size_shader);
}

VertexShaderPtr ShaderLibrary::getVertexShader(String vertex_shader_name)
{
    auto it = m_active_vertex_shaders.find(vertex_shader_name);
    if (it == m_active_vertex_shaders.end())
    {
        throw std::exception("Vertex Shader not found");
    }
    else
    {
        return it->second;
    }
}

PixelShaderPtr ShaderLibrary::getPixelShader(String pixel_shader_name)
{
    auto it = m_active_pixel_shaders.find(pixel_shader_name);
    if (it == m_active_pixel_shaders.end())
    {
        throw std::exception("Pixel Shader not found");
    }
    else
    {
        return it->second;
    }
}

ShaderLibrary::ShaderLibrary()
{
    GraphicsEngine* graphics_engine = GraphicsEngine::getInstance();

    ShaderNames shader_names;
    ShaderData shader_data;

    /* Vertex Shaders */
    graphics_engine->getRenderSystem()->compileVertexShader(shader_names.VERTEX_MESH_LAYOUT_SHADER_NAME.c_str(), "vsmain", &shader_data.m_shader_byte_code, &shader_data.m_size_shader);
    this->m_active_vertex_shaders[shader_names.VERTEX_MESH_LAYOUT_SHADER_NAME]
        = graphics_engine->getRenderSystem()->createVertexShader(shader_data.m_shader_byte_code, shader_data.m_size_shader);

   // graphics_engine->getRenderSystem()->compileVertexShader(shader_names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shader_data.m_shader_byte_code, &shader_data.m_size_shader);
   // this->m_active_vertex_shaders[shader_names.BASE_VERTEX_SHADER_NAME]
   //    = graphics_engine->getRenderSystem()->createVertexShader(shader_data.m_shader_byte_code, shader_data.m_size_shader);

    graphics_engine->getRenderSystem()->compileVertexShader(shader_names.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shader_data.m_shader_byte_code, &shader_data.m_size_shader);
    this->m_active_vertex_shaders[shader_names.TEXTURED_VERTEX_SHADER_NAME]
        = graphics_engine->getRenderSystem()->createVertexShader(shader_data.m_shader_byte_code, shader_data.m_size_shader);

    /* Pixel Shaders */
    graphics_engine->getRenderSystem()->compilePixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shader_data.m_shader_byte_code, &shader_data.m_size_shader);
    this->m_active_pixel_shaders[shader_names.TEXTURED_PIXEL_SHADER_NAME]
        = graphics_engine->getRenderSystem()->createPixelShader(shader_data.m_shader_byte_code, shader_data.m_size_shader);

    //graphics_engine->getRenderSystem()->compilePixelShader(shader_names.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shader_data.m_shader_byte_code, &shader_data.m_size_shader);
    //this->m_active_pixel_shaders[shader_names.BASE_PIXEL_SHADER_NAME]
    //   = graphics_engine->getRenderSystem()->createPixelShader(shader_data.m_shader_byte_code, shader_data.m_size_shader);
}

ShaderLibrary::~ShaderLibrary()
{
}
