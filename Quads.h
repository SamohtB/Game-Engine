#pragma once
#include "GameObject.h"

class FoldingQuad : public GameObject
{
public:
	FoldingQuad()
	{
		this->vertices =
		{
			{-0.8f, -1.0f, 0.0f, -0.5f, -0.5f, 0.0f,	1.f, 1.f, 0.f,	1.f, 1.f, 0.f}, // top left
			{-1.0f,  0.0f, 0.0f, -0.1f,  0.7f, 0.0f,	1.f, 1.f, 1.f,	0.f, 0.f, 1.f}, // top right
			{ 1.0f, -0.2f, 0.0f,  0.2f, -0.5f, 0.0f, 	0.f, 0.f, 1.f,	1.f, 0.f, 0.f}, // bottom left
			{-0.8f, -1.0f, 0.0f,  0.7f,  0.7f, 0.0f,	0.f, 0.f, 0.f,	0.f, 1.f, 0.f},	// top left
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
			{-0.7f, -0.9f, 0.0f,    -0.32f, -0.11f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
			{-0.8f,  0.2f, 0.0f,    -0.11f,  0.78f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
			{0.3f,  -0.3f, 0.0f,     0.75f, -0.73f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f},
			{0.0f,   0.2f, 0.0f,     0.88f,  0.77f, 0.0f,		0.9f, 0.54f, 0.9f,	0.6f, 0.9f, 0.54f}
		};
	}

	~LoopedQuad() {}

};

