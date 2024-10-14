#pragma once
#include <stack>
#include <vector>
#include <iostream>
#include <random>

#include "Circle.h"

class CircleManager
{
public:
	CircleManager();
	~CircleManager();

	void update(float deltaTime);
	void draw();
	void setConstants(DeviceContext* context, void* buffer);
	void CreateCirclePool(int amount);

	void clearCircles();
	void clearNewestCircle();
	Circle* spawnCircle();
	void spawnBatch(int amount);

	void setRadius(float radius);
	void setSpeed(float speed);
	void setWindowParameters(float width, float height);

private:
	static std::random_device rd;
	static std::mt19937 gen;
	std::uniform_real_distribution<float> dis;

	std::stack<Circle*> activeCircles;
	std::vector<Circle*> circlePool;

	float radius = 0.05f;
	float speed = 0.5f;
	float windowWidth = 0;
	float windowHeight = 0;
};

