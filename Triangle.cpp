#include "Triangle.h"

void Triangle::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(this->vertexBuffer->getSizeVertexList(), 0);
}