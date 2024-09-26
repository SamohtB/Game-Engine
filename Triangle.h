#pragma once
#include "GameObject.h"

class GraphicsEngine;
class DeviceContext;

class Triangle : public GameObject
{
public:
	Triangle(vertex* data) : GameObject(data) {}
	~Triangle() {}

	void draw() override;
};