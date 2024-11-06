#include "AppWindow.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <random>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	/* Engine Component Initialization */
	GraphicsEngine::initialize();
	EngineTime::initialize();
	InputSystem::initialize();

	EngineTime::setFrameTime(60);
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(false);
	
	RECT rc = this->getClientWindowRect();
	this->m_window_width = rc.right - rc.left;
	this->m_window_height = rc.bottom - rc.top;
	m_swap_chain->init(this->m_hwnd, this->m_window_width, this->m_window_height);

	Cube* cube = nullptr;
	this->gameObjectManager = new GameObjectManager();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> posDist(-0.75f, 0.75f);
	std::uniform_real_distribution<float> speedDist(-2.0f, 2.0f);

	for (int i = 0; i < 1; i++)
	{
		cube = new Cube();
		cube->setSize(0.15f);
		cube->initialize();
		cube->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
		cube->setPosition(XMVECTOR{ 0, 0.25, 0 });
		cube->setSpeed(speedDist(gen));
		gameObjectManager->registerObject(cube);
	}

	rotatedObject = cube;

	Plane* plane = new Plane();
	plane->setSize(0.45f);
	plane->initialize();
	plane->loadShaders(L"VertexShader.hlsl", "vsmain", L"PixelShader.hlsl", "psmain");
	plane->setPosition(XMVECTOR{ 0, 0, 0 });
	gameObjectManager->registerObject(plane);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3f, 0.2f, 0.4f, 1);
	
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(m_window_width, m_window_height);

	/* Inputs */
	InputSystem::getInstance()->update();

	/* Updates */
	updateGameObjects();

	/* Draws */
	drawGameObjects();

	m_swap_chain->present(true);
}

void AppWindow::updateGameObjects()
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());
	float speed = 0.3f;

	/* Get Rotation and Directions */
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(x_rotate, y_rotate, 0.0f);
	XMVECTOR forwardVector = XMVector3TransformCoord(XMLoadFloat3(new XMFLOAT3(0.0f, 0.0f, 1.0f)), rotationMatrix);
	XMVECTOR rightVector = XMVector3TransformCoord(XMLoadFloat3(new XMFLOAT3(1.0f, 0.0f, 0.0f)), rotationMatrix);

	/* Calculate Movement */
	XMVECTOR movementVector = (forwardVector * forward + rightVector * strafe);

	if (XMVector3Length(movementVector).m128_f32[0] > 0.0f)
	{
		movementVector = XMVector3Normalize(movementVector) * speed * deltaTime;
	}

	/* Update Camera Position */
	XMVECTOR currentCameraPosition = m_world_camera.r[3];
	XMVECTOR newCameraPosition = currentCameraPosition + movementVector;

	/* Update Camera World Matrix with new Position */
	m_world_camera = rotationMatrix;
	m_world_camera.r[3] = newCameraPosition;
	
	/* Transform to View Matrix by inverting */
	XMMATRIX viewMatrix = XMMatrixInverse(nullptr, m_world_camera);

	float fov = XM_PIDIV4;
	float aspectRatio = static_cast<float>(m_window_height / m_window_height);
	float nearZ = 0.01f;
	float farZ = 100.0f;
	XMMATRIX projection_matrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);

	gameObjectManager->setViewMatrix(viewMatrix);
	gameObjectManager->setProjectionMatrix(projection_matrix);
	gameObjectManager->update(deltaTime);
}

void AppWindow::drawGameObjects()
{
	gameObjectManager->draw(this->m_window_width, this->m_window_height);
}

void AppWindow::onKeyDown(int key)
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());

	if (key == 'W')
	{
		forward = 1.0f;
	}

	else if (key == 'S')
	{
		forward = -1.0f;
	}

	if (key == 'A')
	{
		strafe = -1.0f;
	}

	else if (key == 'D')
	{
		strafe = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W' || key == 'S')
	{
		forward = 0.0f;
	}
	if (key == 'A' || key == 'D')
	{
		strafe = 0.0f;
	}
}

void AppWindow::onMouseMove(const XMFLOAT2& mouse_pos)
{
	float deltaTime = static_cast<float>(EngineTime::getFixedDeltaTime());
	float sensitivity = 0.1f;

	x_rotate += (mouse_pos.y - (m_window_height / 2.0f)) * sensitivity * deltaTime;
	y_rotate += (mouse_pos.x - (m_window_width / 2.0f)) * sensitivity * deltaTime;

	InputSystem::getInstance()->setCursorPosition(XMFLOAT2(m_window_width / 2.0f, m_window_height / 2.0f));
}

void AppWindow::onLeftMouseDown(const XMVECTOR& mouse_pos)
{
	rotatedObject->setScale(0.5f, 0.5f, 0.5f);
}

void AppWindow::onLeftMouseUp(const XMVECTOR& mouse_pos)
{
	rotatedObject->setScale(1.f, 1.f, 1.f);
}

void AppWindow::onRightMouseDown(const XMVECTOR& mouse_pos)
{
	rotatedObject->setScale(2.f, 2.f, 2.f);
}

void AppWindow::onRightMouseUp(const XMVECTOR& mouse_pos)
{
	rotatedObject->setScale(1.f, 1.f, 1.f);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::destroy();
	InputSystem::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}