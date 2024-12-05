#pragma once
#include "AResourceManager.h"
#include "Prerequisites.h"

class TextureNames
{
public:
    typedef const wchar_t* String;

    const String BRICK = L"Assets\\Textures\\wood.jpg";
    const String WOOD = L"Assets\\Textures\\brick.png";
    const String SAND = L"Assets\\Textures\\sand.jpg";
};

class TextureManager : public AResourceManager
{
public:
    TextureManager();
    ~TextureManager();

    enum TextureType {
        NONE = -1,
        BRICK = 0,
        WOOD,
        SAND
    };

    TexturePtr createTextureFromFile(const wchar_t* file_path);
    TexturePtr createTextureFromFile(TextureType type);

protected:
    Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
};
