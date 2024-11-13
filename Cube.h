#pragma once
#include "GameObject.h"
#include "RenderSystem.h"

class Cube : public GameObject
{
public:
    Cube(float size);
    ~Cube();

    void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);
    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix) override;

protected:
    static const int NUM_VERTICES = 8;
    static const int NUM_INDICES = 36;

    vertex m_vertex_list[NUM_VERTICES];
    unsigned int m_index_list[NUM_INDICES];

    float m_ticks = 0.0f;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;
    VertexShaderPtr m_vertex_shader = nullptr;
    PixelShaderPtr m_pixel_shader = nullptr;
};
