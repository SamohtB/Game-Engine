#include "Quad.h"

void Quad::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexBuffer->getSizeVertexList(), 0);
}