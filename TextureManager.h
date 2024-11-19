#pragma once
#include "AResourceManager.h"
#include "Prerequisites.h"

class TextureManager : public AResourceManager
{
public:
    TextureManager();
    ~TextureManager();

    TexturePtr createTextureFromFile(const wchar_t* file_path);

protected:
    Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
};
