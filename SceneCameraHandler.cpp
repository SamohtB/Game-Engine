#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler::SceneCameraHandler(float width, float height)
{
	m_scene_camera = new Camera("Scene Camera", width, height);
    m_scene_camera->setPosition(0.0f, 0.0f, -5.0f);
}

SceneCameraHandler::~SceneCameraHandler() 
{
	delete m_scene_camera;
}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize(float width, float height)
{
	try
	{
		sharedInstance = new SceneCameraHandler(width, height);
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
	sharedInstance->m_scene_camera->update(deltaTime);
}

XMMATRIX SceneCameraHandler::getSceneCameraViewMatrix()
{
	return sharedInstance->m_scene_camera->getViewMatrix();
}

XMMATRIX SceneCameraHandler::getSceneCameraProjMatrix()
{
	return sharedInstance->m_scene_camera->getProjectionMatrix();
}

void SceneCameraHandler::setScreenSize(float width, float height)
{
	this->m_scene_camera->setScreenParams(width, height);
}

Camera* SceneCameraHandler::getCamera()
{
	return sharedInstance->m_scene_camera;
}
