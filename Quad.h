#pragma once
#include "GameObject.h"

class Quad : public GameObject
{
public:
    Quad();
    ~Quad();

    virtual void initialize() override;
    void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry);
    virtual void update(float deltaTime) override;
    virtual void draw(int width, int height, XMMATRIX view_matrix, XMMATRIX projection_matrix, ID3D11ShaderResourceView* srv) override;
    void release();

    void setSize(float size);

protected:
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