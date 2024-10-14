#pragma once
#include "Object2D.h"
#include <algorithm>

class Circle : public Object2D
{
public:
	Circle(float radius, XMFLOAT3 color, int segments = 32);
	~Circle() {}

	void initialize(float posX, float posY, float dirX, float dirY);
	void update(float deltaTime) override;

	void setDirection(float x, float y);
	void setSpeed(float speed);

private:
	std::vector<vertex> GenerateCircleVertices(float radius, int segmentCount);
	void handleCollision();

	XMFLOAT3 color = {};
	XMFLOAT2 direction;
	float moveSpeed = 1.0f;
};
