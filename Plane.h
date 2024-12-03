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
    VertexBufferPtr m_vertex_buffer = nullptr;
    ConstantBufferPtr m_constant_buffer = nullptr;
    IndexBufferPtr m_index_buffer = nullptr;

private:
    void buildShape(float width, float height);
};
