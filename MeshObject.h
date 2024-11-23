#pragma once
#include "AGameObject.h"
#include "RenderSystem.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"

class MeshObject :  public AGameObject
{
public:
    MeshObject(const wchar_t* mesh_file_path);
    ~MeshObject();

    // Inherited via AGameObject
    void update(float deltaTime) override;
    void draw(int width, int height) override;

private:
    ConstantBufferPtr m_constant_buffer = nullptr;
    MeshPtr m_mesh = nullptr;

    friend class Mesh;
};

