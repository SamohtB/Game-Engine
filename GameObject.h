#pragma once
#include "VertexBuffer.h"

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

	virtual void draw(ID3D11DeviceContext* m_device_context) = 0;

protected:
	VertexBuffer* vertexBuffer;

};

