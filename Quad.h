#pragma once
#include "GameObject.h"

class GraphicsEngine;
class DeviceContext;

class Quad : public GameObject
{
public:
	Quad() : GameObject() {}
	~Quad() {}

	void initialize(float width, float height, vec3 initialPosition, vec3 color);
};