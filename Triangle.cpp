#include "Triangle.h"

void Triangle::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(this->vertexBuffer->getSizeVertexList(), 0);
}