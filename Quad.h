#pragma once
#include "GameObject.h"

class GraphicsEngine;
class DeviceContext;

class Quad : public GameObject
{
public:
	Quad(vertex* data) : GameObject(data) {}
	~Quad() {}

	void draw() override;
};