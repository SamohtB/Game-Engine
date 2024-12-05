#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"

using namespace DirectX;

class Sphere : public AGameObject
{
public:
    Sphere(String name, float radius = 1, XMFLOAT3 color = XMFLOAT3(1.0f, 1.0f, 1.0f));
    ~Sphere();

    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height) override;

protected:
    static const int NUM_RINGS = 20;
    static const int NUM_SECTORS = 20;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;

private:
    virtual void buildShape(float radius, XMFLOAT3 color);
};

