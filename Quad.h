#pragma once
#include <string>
#include "GameObject.h"

class Quad : public GameObject
{
public:
	Quad(std::string name, vertex list);

	void draw(ID3D11DeviceContext* m_device_context) override;
};

