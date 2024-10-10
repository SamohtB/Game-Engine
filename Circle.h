#pragma once
#include "GameObject.h"

#ifndef PI
#define PI 3.14159265359f
#endif

class Circle : public GameObject
{
public:
	Circle(float radius, XMFLOAT3 color, int segments = 32);
	~Circle() {}

	void update(float deltaTime) override; 

private:
	std::vector<vertex> GenerateCircleVertices(float radius, int segmentCount);

	XMFLOAT3 color = {};
};
