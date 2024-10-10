#include "Circle.h"

Circle::Circle(float radius, XMFLOAT3 color, int segments)
{
    this->color = color;
    this->vertices = GenerateCircleVertices(radius, segments);
}

void Circle::initialize(float x, float y)
{
	this->position = XMFLOAT3(0, 0, 0);
	this->rotation = XMFLOAT3(0, 0, 0);
	this->scale = XMFLOAT3(1, 1, 1);

	this->setDirection(x, y);
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

bool Circle::checkCollision()
{

	return true;
}