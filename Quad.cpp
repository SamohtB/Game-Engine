#include "Quad.h"

void Quad::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexBuffer->getSizeVertexList(), 0);
}