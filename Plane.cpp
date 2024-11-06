#include "Plane.h"

Plane::Plane() {}

Plane::~Plane() {}

void Plane::initialize()
{
    this->active = true;

    this->vertices.clear();

    this->vertices.push_back({ XMFLOAT3(-m_size, -m_size, 0.01f), XMFLOAT3(1.0f, 1.0f, 1.0f) }); // Bottom left
    this->vertices.push_back({ XMFLOAT3(-m_size, 0.01f,  m_size), XMFLOAT3(1.0f, 1.0f, 1.0f) }); // Top left
    this->vertices.push_back({ XMFLOAT3(m_size,  0.01f, m_size), XMFLOAT3(1.0f, 1.0f, 1.0f) });  // Top right
    this->vertices.push_back({ XMFLOAT3(m_size, -m_size, 0.01f), XMFLOAT3(1.0f, 1.0f, 1.0f) });  // Bottom right

    this->index_list = {
        // Plane face
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };
}


void Plane::update(float deltaTime) {}
