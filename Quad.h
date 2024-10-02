#pragma once
#include "GameObject.h"

class GraphicsEngine;
class DeviceContext;

class Quad : public GameObject
{
public:
	Quad() : GameObject() {}
	~Quad() {}

	void draw() override;
};