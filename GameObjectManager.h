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

	void setViewMatrix(XMMATRIX view_matrix);
	void setProjectionMatrix(XMMATRIX projection_matrix);

private:
	std::vector<GameObject*> objectList;
	XMMATRIX currentViewMatrix = XMMatrixIdentity();
	XMMATRIX currentProjectionMatrix = XMMatrixIdentity();
};


