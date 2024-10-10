#pragma once
#include "GameObject.h"

#ifndef PI
#define PI 3.14159265359f
#endif

class Circle : public GameObject
{
public:
	Circle(float radius, Vector3D color)
	{
        this->color = color;
        this->vertices = GenerateCircleVertices(radius, 8);
	}
	~Circle() {};

private:
    Vector3D color = {};

private:
    std::vector<vertex> GenerateCircleVertices(float radius, int segmentCount)
    {
        std::vector<vertex> vertices(segmentCount);

        float angleStep = 2 * PI / segmentCount;

        for (int i = 0; i < segmentCount; ++i)
        {
            float angle = i * angleStep;
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            vertices[i].position = Vector3D(x, y, 0.0f);
            vertices[i].position1 = Vector3D(x, y, 0.0f);
            vertices[i].color = this->color;
            vertices[i].color1 = this->color;
        }

        vertex firstElement = vertices[0];
        vertices.push_back(firstElement);

        return vertices;
    }

};