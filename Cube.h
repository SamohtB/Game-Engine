#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
    Cube();
    ~Cube();

    void initialize() override;
    void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);
    void update(float deltaTime) override;
    virtual void draw(int width, int height) override;
    void release();

    void setSize(float size);
    void setSpeed(float speed);

private:
    std::vector<vertex> vertices;
    std::vector<unsigned int> index_list;

    float m_size = 0.0f;
    float m_ticks = 0.0f;
    float m_delta_pos = 0.0f;
    float m_delta_time = 0.0f;
    float m_speed = 0.5f;

    VertexBuffer* vertexBuffer = nullptr;
    ConstantBuffer* constantBuffer = nullptr;
    IndexBuffer* indexBuffer = nullptr;
    VertexShader* vertexShader = nullptr;
    PixelShader* pixelShader = nullptr;
};
