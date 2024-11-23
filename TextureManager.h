#pragma once
#include "Texture.h"

#include <string>
#include <unordered_map>

class TextureNames
{
public:
    typedef std::wstring String;

    const String BRICK_TEXTURE = L"Assets\\Textures\\brick.png";
};

class TextureManager
{
public:
    typedef std::wstring String;
    typedef std::unordered_map<String, Texture*> TextureMap;

    static TextureManager* getInstance();
    static void initialize();
    static void destroy();

    Texture* getTexture(String texture_name);

private:
    TextureManager();
    ~TextureManager();
    TextureManager(TextureManager const&) {}
    TextureManager& operator=(TextureManager const&) {}

    static TextureManager* sharedInstance;

    TextureMap textureMap;
protected:
    Texture* createTextureFromFile(const wchar_t* file_path);
};
