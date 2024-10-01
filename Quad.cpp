#include "Quad.h"

void Quad::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexBuffer->getSizeVertexList(), 0);
}