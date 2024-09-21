#pragma once
#include "GameObject.h"
#include "DeviceContext.h"

class GraphicsEngine;
class DeviceContext;

class Triangle : public GameObject
{
public:
	Triangle(vertex* data) : GameObject(data) {}
	~Triangle() {}

	void draw() override;
};