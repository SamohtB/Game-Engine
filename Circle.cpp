#include "Circle.h"
#include <iostream>

Circle::Circle(float radius, XMFLOAT3 color, int segments)
{
    this->color = color;
    this->vertices = GenerateCircleVertices(radius, segments);
}

void Circle::initialize(float posX, float posY, float dirX, float dirY)
{
	this->position = XMFLOAT3(posX, posY, 0);
	this->setDirection(dirX, dirY);
}

std::vector<vertex> Circle::GenerateCircleVertices(float radius, int segmentCount)
{
	std::vector<vertex> vertices;

	vertex center =
	{
		XMFLOAT3(0, 0, 0),
		this->color,
	};

	float angleStep = XM_2PI / segmentCount;

	for (int i = 0; i < segmentCount; ++i)
	{
		float angle = i * angleStep;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);

		vertex currentVertex =
		{
			XMFLOAT3(x, y, 0.0f),
			this->color
		};

		float nextAngle = (i + 1) % segmentCount * angleStep;
		float nextX = radius * cosf(nextAngle);
		float nextY = radius * sinf(nextAngle);

		vertex nextVertex =
		{
			XMFLOAT3(nextX, nextY, 0.0f),
			this->color
		};

		vertices.push_back(center);
		vertices.push_back(currentVertex);
		vertices.push_back(nextVertex);
	}

	return vertices;
}

void Circle::update(float deltaTime)
{
	this->position.x += this->direction.x * this->moveSpeed * deltaTime;
	this->position.y += this->direction.y * this->moveSpeed * deltaTime;

	handleCollision();

	GameObject::update(deltaTime);
}

void Circle::setDirection(float x, float y)
{
	XMVECTOR dir = XMVectorSet(x, y, 0.0f, 0.0f);
	dir = XMVector2Normalize(dir);
	XMStoreFloat2(&this->direction, dir);
}

void Circle::setSpeed(float speed)
{
	this->moveSpeed = speed;
}

void Circle::handleCollision()
{
	XMVECTOR pos = XMLoadFloat3(&this->position); 
	XMVECTOR dir = XMLoadFloat2(&this->direction);

	float radius = 0.05f;
	bool isColliding = false;

	if (XMVectorGetY(pos) + radius > 1.8f)
	{
		float penetration = (XMVectorGetY(pos) + radius) - 1.8f;
		pos = XMVectorSubtract(pos, XMVectorSet(0, penetration, 0, 0));
		dir = XMVectorSetY(dir, -XMVectorGetY(dir));
		isColliding = true;
	}
	
	else if (XMVectorGetY(pos) - radius < -1.8f)
	{
		float penetration = -1.8f - (XMVectorGetY(pos) - radius);
		pos = XMVectorAdd(pos, XMVectorSet(0, penetration, 0, 0));
		dir = XMVectorSetY(dir, -XMVectorGetY(dir));
		isColliding = true;
	}

	
	if (XMVectorGetX(pos) - radius < -2.5f)
	{
		float penetration = -2.5f - (XMVectorGetX(pos) - radius);
		pos = XMVectorAdd(pos, XMVectorSet(penetration, 0, 0, 0));
		dir = XMVectorSetX(dir, -XMVectorGetX(dir));
		isColliding = true;
	}

	else if (XMVectorGetX(pos) + radius > 2.5f)
	{
		float penetration = (XMVectorGetX(pos) + radius) - 2.5f;
		pos = XMVectorSubtract(pos, XMVectorSet(penetration, 0, 0, 0));
		dir = XMVectorSetX(dir, -XMVectorGetX(dir));
		isColliding = true;
	}

	if (isColliding)
	{
		XMStoreFloat3(&this->position, pos);
		XMStoreFloat2(&this->direction, dir);
	}
}