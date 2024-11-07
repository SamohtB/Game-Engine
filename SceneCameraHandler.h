#pragma once
#include "Camera.h"
#include "EngineTime.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();
	XMMATRIX getSceneCameraViewMatrix();
	XMMATRIX getSceneCameraProjMatrix();
	void setScreenSize(float width, float height);
	Camera* getCamera();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {}
	SceneCameraHandler& operator=(SceneCameraHandler const&) {}

	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera = nullptr;

	float fov = XM_PIDIV4;
	float aspectRatio = 0.0f;
	float nearZ = 0.01f;
	float farZ = 100.0f;
};