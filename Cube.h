#pragma once
#include "AGameObject.h"
#include "RenderSystem.h"
#include "SceneCameraHandler.h"

using namespace DirectX;

class Cube : public AGameObject
{
public:
    Cube(float size);
    ~Cube();

    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height) override;

protected:
    static const int NUM_VERTICES = 24;
    static const int NUM_INDICES = 36;

    vertex m_vertex_list[NUM_VERTICES];
    unsigned int m_index_list[NUM_INDICES];

    float m_ticks = 0.0f;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;
};
