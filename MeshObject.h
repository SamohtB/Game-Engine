#pragma once
#include "AGameObject.h"
#include "RenderSystem.h"

class MeshObject :  public AGameObject
{
public:
    MeshObject(const wchar_t* mesh_file_path, const wchar_t* texture_file_path, const wchar_t* vs_path, const wchar_t* ps_path);
    ~MeshObject();

    // Inherited via AGameObject
    void update(float deltaTime) override;
    void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix) override;

private:
    ConstantBufferPtr m_constant_buffer = nullptr;
    VertexShaderPtr m_vertex_shader = nullptr;
    PixelShaderPtr m_pixel_shader = nullptr;
    TexturePtr m_texture = nullptr;
    MeshPtr m_mesh = nullptr;

    friend class Mesh;
};

