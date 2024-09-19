#include "Quad.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

void Quad::draw(ID3D11DeviceContext* m_device_context)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(this->vertexBuffer->getSizeVertexList(), 0);
}
