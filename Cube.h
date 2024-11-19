#pragma once
#include "GameObject.h"
#include "RenderSystem.h"

using namespace DirectX;

class Cube : public AGameObject
{
public:
    Cube(float size);
    ~Cube();

    void loadTexture(const wchar_t* texture_path);
    void loadShaders(const wchar_t* vs_path, const char* vs_entry, const wchar_t* ps_path, const char* psEntry);
    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix) override;

protected:
    static const int NUM_VERTICES = 24;
    static const int NUM_INDICES = 36;

    vertex m_vertex_list[NUM_VERTICES];
    unsigned int m_index_list[NUM_INDICES];

    float m_ticks = 0.0f;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;
    VertexShaderPtr m_vertex_shader = nullptr;
    PixelShaderPtr m_pixel_shader = nullptr;
    TexturePtr m_texture = nullptr;
};
