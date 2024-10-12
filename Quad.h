#pragma once
#include "GameObject.h"

class GraphicsEngine;
class DeviceContext;

class Quad : public GameObject
{
public:
	Quad() : GameObject() {}
	~Quad() {}

	void setParameters(float width, float height, vec3 initialPosition, vec3 color);
};