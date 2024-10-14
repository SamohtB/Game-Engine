#include "Object2D.h"

void Object2D::draw()
{
	GameObject::draw();

	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	context->draw(this->vertexBuffer->getSizeVertexList(), 0, m_topology);
}