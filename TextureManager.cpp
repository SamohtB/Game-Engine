#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager::TextureManager() : AResourceManager()
{

}

TextureManager::~TextureManager()
{

}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
    return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

TexturePtr TextureManager::createTextureFromFile(TextureType type)
{
    TextureNames names; 
    switch (type)
    {
    case BRICK: return createTextureFromFile(names.BRICK);
    case WOOD: return createTextureFromFile(names.WOOD);
    case SAND: return createTextureFromFile(names.SAND);
    default: std::cout << "Texture Missing!" << std::endl;
    }
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
    Texture* tex = nullptr;

    try
    {
        tex = new Texture(file_path);
    }
    catch (...)
    {
        throw std::exception("Texture nor created successfully");
    }

    return tex;
}
