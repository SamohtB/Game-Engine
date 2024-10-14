#include "CircleManager.h"

std::random_device CircleManager::rd;
std::mt19937 CircleManager::gen(CircleManager::rd());

CircleManager::CircleManager() : dis(-1.0f, 1.0f) {}

CircleManager::~CircleManager()
{
	for (Circle* circle : circlePool)
	{
		delete circle;
	}

	this->circlePool.clear();
}

void CircleManager::CreateCirclePool(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Circle* circle = new Circle(this->radius, XMFLOAT3(1.f, 1.f, 1.f));
		circle->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
		circle->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		circle->setSpeed(this->speed);
		circle->setActive(false);

		this->circlePool.push_back(circle);
	}
}

void CircleManager::clearCircles()
{
	if (!this->activeCircles.empty())
	{
		while (!this->activeCircles.empty())
		{
			Circle* circle = this->activeCircles.top();
			circle->setActive(false);
			this->activeCircles.pop();
		}
	}
}

void CircleManager::clearNewestCircle()
{
	if (!this->activeCircles.empty())
	{
		Circle* circle = this->activeCircles.top();
		circle->setActive(false);
		this->activeCircles.pop();
	}
}

Circle* CircleManager::spawnCircle()
{
	if (!this->circlePool.empty())
	{
		for (Circle* circle : this->circlePool)
		{
			if (!circle->isActive())
			{
				circle->setActive(true);
				circle->initialize(dis(gen), dis(gen), dis(gen), dis(gen));
				this->activeCircles.push(circle);
				return circle;
			}
		}
		
		std::cout << "Insufficient Circles!" << std::endl;
		return nullptr; 
	}

	std::cout << "Pool Empty!" << std::endl;
	return nullptr;
}

void CircleManager::spawnBatch(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Circle* circle = spawnCircle();

		if (circle == nullptr)
		{
			std::cout << "Insufficient Circles For Batch!" << std::endl;
			return;
		}
	}
}

void CircleManager::setWindowParameters(float width, float height)
{
	this->windowWidth = width;
	this->windowHeight = height;
}

void CircleManager::setSpeed(float speed)
{
	this->speed = speed;
}

void CircleManager::setRadius(float radius)
{
	this->radius = speed;
}

void CircleManager::update(float deltaTime)
{
	for (Circle* circle : circlePool)
	{
		if (circle->isActive())
		{
			circle->update(deltaTime);
		}
	}
}

void CircleManager::setConstants(DeviceContext* context, void* buffer)
{
	for (Circle* circle : circlePool)
	{
		if (circle->isActive())
		{
			circle->setConstants(context, buffer);
		}
	}
}

void CircleManager::draw()
{
	for (Circle* circle : circlePool)
	{
		if (circle->isActive())
		{
			circle->draw();
		}
	}
}