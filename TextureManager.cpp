#include "TextureManager.h"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager::TextureManager()
{
    TextureNames textureNames;

    this->textureMap[textureNames.BRICK_TEXTURE] = createTextureFromFile(static_cast<const wchar_t*>(textureNames.BRICK_TEXTURE.c_str()));
}

TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::getInstance()
{
    return sharedInstance;
}

void TextureManager::initialize()
{
    sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
    delete sharedInstance;
}

Texture* TextureManager::getTexture(String texture_name)
{
    return this->textureMap[texture_name];
}

Texture* TextureManager::createTextureFromFile(const wchar_t* file_path)
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

