#include "Triangle.h"

void Triangle::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(this->vertexBuffer->getSizeVertexList(), 0);
}