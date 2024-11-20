#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class VertexMesh
{
public:
    VertexMesh() : m_position(), m_texcoord() {}
    VertexMesh(XMFLOAT3 position, XMFLOAT2 texcoord) : m_position(position), m_texcoord(texcoord) {}
    VertexMesh(const VertexMesh& vertex) : m_position(vertex.m_position), m_texcoord(vertex.m_texcoord) {}
    ~VertexMesh() {}

    XMFLOAT3 m_position;
    XMFLOAT2 m_texcoord;
};
