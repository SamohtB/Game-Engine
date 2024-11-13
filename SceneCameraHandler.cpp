#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	sharedInstance = new SceneCameraHandler();
	sharedInstance->sceneCamera = new Camera();
	sharedInstance->sceneCamera->setPosition(0.0f, 0.0f, -2.0f);
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

SceneCameraHandler::SceneCameraHandler() {}

SceneCameraHandler::~SceneCameraHandler() {}
