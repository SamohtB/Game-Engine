#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"
#include "ObjectRenderer.h"

class Capsule : public AGameObject
{
public:
    Capsule(String name, float radius = 1, float height = 2, XMFLOAT3 color = XMFLOAT3(1.0f, 1.0f, 1.0f));
    ~Capsule();

    virtual void update(float deltaTime) override;
    virtual void draw(int radius, int height) override;

protected:
    static const int NUM_SLICES = 20;
    static const int NUM_STACKS = 20;

    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;

private:
    void buildShape(float radius, float height, XMFLOAT3 color);
};

