#pragma once
#include "GameObject.h"

class Quad : public GameObject
{
public:
	Quad()
	{
		this->vertices =
		{
			{ Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(-0.5f,-0.5f,0.0f),  Vector3D(0,0,0), Vector3D(0,1,0) },
			{ Vector3D(-0.5f,0.5f,0.0f),     Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) },
			{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(0.5f,-0.5f,0.0f),   Vector3D(0,0,1), Vector3D(1,0,0) },
			{ Vector3D(0.5f,0.5f,0.0f),      Vector3D(0.5f,0.5f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) }
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
			vertex{ Vector3D(-0.8f, -1.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1.0f, 1.0f, 1.0f), Vector3D(1.0f, 1.0f, 0.0f) }, // top left
			vertex{ Vector3D(-1.0f,  0.0f, 0.0f), Vector3D(-0.1f, 0.7f, 0.0f), Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f) }, // top right
			vertex{ Vector3D(1.0f, -0.2f, 0.0f), Vector3D(0.2f, -0.5f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector3D(1.0f, 0.0f, 0.0f) }, // bottom left
			vertex{ Vector3D(-0.8f, -1.0f, 0.0f), Vector3D(0.7f, 0.7f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f) }  // bottom left
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
			vertex{ Vector3D(-0.7f, -0.9f, 0.0f), Vector3D(-0.32f, -0.11f, 0.0f), Vector3D(0.9f, 0.54f, 0.9f), Vector3D(0.6f, 0.9f, 0.54f) },
			vertex{ Vector3D(-0.8f,  0.2f, 0.0f), Vector3D(-0.11f, 0.78f, 0.0f), Vector3D(0.9f, 0.54f, 0.9f), Vector3D(0.6f, 0.9f, 0.54f) },
			vertex{ Vector3D(0.3f,  -0.3f, 0.0f), Vector3D(0.75f, -0.73f, 0.0f), Vector3D(0.9f, 0.54f, 0.9f), Vector3D(0.6f, 0.9f, 0.54f) },
			vertex{ Vector3D(0.0f,   0.2f, 0.0f), Vector3D(0.88f,  0.77f, 0.0f), Vector3D(0.9f, 0.54f, 0.9f), Vector3D(0.6f, 0.9f, 0.54f) }
		};
	}

	~LoopedQuad() {}

};

