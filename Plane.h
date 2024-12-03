#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"

class Plane : public AGameObject
{
public:
    Plane(String name, float width = 1, float height = 1);
    ~Plane();

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

private:
    void buildShape(float width, float height);
};
