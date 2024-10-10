#pragma once
#include "GameObject.h"

class Circle : public GameObject
{
public:
	Circle(float radius, XMFLOAT3 color, int segments = 32);
	~Circle() {}

	void update(float deltaTime) override; 

	void setDirection(float x, float y);
	void setSpeed(float speed);

private:
	std::vector<vertex> GenerateCircleVertices(float radius, int segmentCount);

	XMFLOAT3 color = {};
	XMFLOAT2 direction;
	float moveSpeed = 1.0f;
};
