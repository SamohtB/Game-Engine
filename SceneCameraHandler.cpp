#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler::SceneCameraHandler()
{
	sceneCamera = new Camera("Scene Camera");
	sceneCamera->setPosition(0.0f, 0.0f, -2.0f);
}

SceneCameraHandler::~SceneCameraHandler() 
{
	delete sceneCamera;
}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	try
	{
		sharedInstance = new SceneCameraHandler();
	}
	catch (...)
	{
		throw std::exception("SceneCameraHandler not created successfully");
	}
}

void SceneCameraHandler::destroy()
{
	delete sharedInstance;
}

void SceneCameraHandler::update()
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());
	sharedInstance->sceneCamera->update(deltaTime);
}

XMMATRIX SceneCameraHandler::getSceneCameraViewMatrix()
{
	return sharedInstance->sceneCamera->getViewMatrix();
}

XMMATRIX SceneCameraHandler::getSceneCameraProjMatrix()
{
	return sharedInstance->sceneCamera->getProjectionMatrix();
}

void SceneCameraHandler::setScreenSize(float width, float height)
{
	this->sceneCamera->setScreenParams(width, height);
}

Camera* SceneCameraHandler::getCamera()
{
	return sharedInstance->sceneCamera;
}
