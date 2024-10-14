#pragma once
#include <stack>
#include <vector>
#include <iostream>

#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void update(float deltaTime);
	void draw(int width, int height);

	void registerObject(GameObject* gameObject);

private:
	std::vector<GameObject*> objectList;
};


