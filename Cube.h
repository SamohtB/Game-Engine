#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"

using namespace DirectX;

class Cube : public AGameObject
{
public:
     Cube(String name, float width = 1, float height = 1);
    ~Cube();

    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height) override;

protected:
    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;

private:
    virtual void buildShape(float width, float height);
};
