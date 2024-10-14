#pragma once
#include "Object2D.h"

class Quad : public GameObject
{
public:
	Quad()
	{
		this->vertices =
		{
			{ XMFLOAT3(-0.5f,-0.5f,0.0f),    XMFLOAT3(0,0,0)},
			{ XMFLOAT3(-0.5f,0.5f,0.0f),     XMFLOAT3(1,1,0)},
			{ XMFLOAT3(0.5f,-0.5f,0.0f),     XMFLOAT3(0,0,1)},
			{ XMFLOAT3(0.5f,0.5f,0.0f),      XMFLOAT3(1,1,1)}
		};
	}

	~Quad() {}

};


class FoldingQuad : public GameObject
{
public:
	FoldingQuad()
	{
		this->vertices =
		{

			vertex{ XMFLOAT3(-0.8f, -1.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) }, // top left
			vertex{ XMFLOAT3(-1.0f,  0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) }, // top right
			vertex{ XMFLOAT3(1.0f, -0.2f, 0.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f) }, // bottom left
			vertex{ XMFLOAT3(-0.8f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }  // bottom left
		};
	}

	~FoldingQuad() {}

};

class LoopedQuad : public GameObject
{
public:
	LoopedQuad()
	{
		this->vertices =
		{
			vertex{ XMFLOAT3(-0.7f, -0.9f, 0.0f), XMFLOAT3(0.9f, 0.54f, 0.9f),  },
			vertex{ XMFLOAT3(-0.8f,  0.2f, 0.0f), XMFLOAT3(0.9f, 0.54f, 0.9f),  },
			vertex{ XMFLOAT3(0.3f,  -0.3f, 0.0f), XMFLOAT3(0.9f, 0.54f, 0.9f),  },
			vertex{ XMFLOAT3(0.0f,   0.2f, 0.0f), XMFLOAT3(0.9f, 0.54f, 0.9f),  }
		};
	}

	~LoopedQuad() {}

};

