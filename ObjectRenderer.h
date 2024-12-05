#pragma once
#include <string>
#include "Prerequisites.h"

class ObjectRenderer
{
protected:
    typedef std::string String;

public:
    void setRenderer(String path);
    String getMaterialPath() const;
    TexturePtr getTexture() const;

private:
    String m_material_path;
    TexturePtr m_texture;
};

