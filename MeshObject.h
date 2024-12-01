#pragma once
#include "AGameObject.h"


class MeshObject :  public AGameObject
{
public:
    MeshObject(String name);
    ~MeshObject();

    // Inherited via AGameObject
    void update(float deltaTime) override;
    void draw(int width, int height) override;

private:
    ConstantBufferPtr m_constant_buffer = nullptr;
    MeshPtr m_mesh = nullptr;

    friend class Mesh;
};

