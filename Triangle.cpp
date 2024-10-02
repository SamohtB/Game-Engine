#include "Triangle.h"

void Triangle::draw()
{
	GameObject::draw();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(this->vertexBuffer->getSizeVertexList(), 0);
}