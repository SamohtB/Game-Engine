#include "Plane.h"

//Plane::Plane() {}
//
//Plane::~Plane() {}
//
//void Plane::initialize()
//{
//    this->active = true;
//
//    this->m_vertex_list.clear();
//
//    this->m_vertex_list.push_back({ XMFLOAT3(-size, -size, 0.01f), XMFLOAT3(1.0f, 1.0f, 1.0f) }); // Bottom left
//    this->m_vertex_list.push_back({ XMFLOAT3(-size, 0.01f,  size), XMFLOAT3(1.0f, 1.0f, 1.0f) }); // Top left
//    this->m_vertex_list.push_back({ XMFLOAT3(size,  0.01f, size), XMFLOAT3(1.0f, 1.0f, 1.0f) });  // Top right
//    this->m_vertex_list.push_back({ XMFLOAT3(size, -size, 0.01f), XMFLOAT3(1.0f, 1.0f, 1.0f) });  // Bottom right
//
//    this->m_index_list = {
//        // Plane face
//        0, 1, 2, // First triangle
//        2, 3, 0  // Second triangle
//    };
//}
//
//
//void Plane::update(float deltaTime) {}
