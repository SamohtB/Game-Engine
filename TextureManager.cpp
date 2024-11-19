#include "TextureManager.h"
#include "Texture.h"

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
