#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"

using namespace DirectX;

class Cylinder : public AGameObject
{
public:
    Cylinder(String name, float width = 1, float height = 2, XMFLOAT3 color = XMFLOAT3(1.0f, 1.0f, 1.0f));
    ~Cylinder();

    virtual void update(float deltaTime) override;
    virtual void draw(int radius, int height) override;

protected:
    static const int NUM_SLICES = 20;
    static const int NUM_STACKS = 20;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;

private:
    void buildShape(float width, float height, XMFLOAT3 color);
};

