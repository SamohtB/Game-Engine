#include "Quad.h"

void Quad::draw()
{
	GameObject::draw();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexBuffer->getSizeVertexList(), 0);
}