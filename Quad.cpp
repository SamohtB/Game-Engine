#include "Quad.h"
#include <iostream>

void Quad::setParameters(float width, float height, vec3 initialPosition, vec3 color)
{
	vertex bot_left = { initialPosition.x - width, initialPosition.y - height, 0.0f, color.x, color.y, color.z };
	vertex top_left = { initialPosition.x - width, initialPosition.y + height, 0.0f, color.x, color.y, color.z };
	vertex bot_right = { initialPosition.x + width, initialPosition.y - height, 0.0f, color.x, color.y, color.z };
	vertex top_right = { initialPosition.x + width, initialPosition.y + height, 0.0f, color.x, color.y, color.z };

	this->m_vertices.push_back(top_right);
	this->m_vertices.push_back(bot_right);
	this->m_vertices.push_back(top_left);
	this->m_vertices.push_back(bot_left);
}
