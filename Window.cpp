#include "Window.h"
#include "EngineTime.h"
#include <iostream>

Window::Window() {}

Window::~Window(){}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}

	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	case WM_KEYDOWN:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (!window->isKeyPressed(wparam)) // Check if the key is already pressed
		{
			switch (wparam)
			{
			case VK_ESCAPE:
				window->onDestroy();
				::PostQuitMessage(1);
				break;
			case VK_BACK:
				window->setBackspace(true);
				break;
			case VK_DELETE:
				window->setDelete(true);
				break;
			case VK_SPACE:
				window->setSpace(true);
				break;
			}
			window->setKeyPressed(wparam, true); // Mark the key as pressed
		}

		break;
	}

	case WM_KEYUP:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		switch (wparam)
		{
		case VK_BACK:
			window->setBackspace(false);
			break;
		case VK_DELETE:
			window->setDelete(false);
			break;
		case VK_SPACE:
			window->setSpace(false);
			break;
		}

		window->setKeyPressed(wparam, false);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

}

bool Window::isKeyPressed(WPARAM key)
{
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}

void Window::setKeyPressed(WPARAM key, bool pressed)
{
	keyStates[key] = pressed;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	//Register
	if (!::RegisterClassEx(&wc))
	{
		return false;
	}

	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	//Create Window
	if (!m_hwnd)
	{
		return false;
	}

	//Show Window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;
	return true;
}

bool Window::broadcast()
{
	EngineTime::LogFrameStart();
	this->onUpdate();
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();

	frameCount++;
	totalTime += EngineTime::sharedInstance->deltaTime;

	if (totalTime >= updateInterval)
	{
		double averageFPS = frameCount / totalTime;
		std::cout << "Average FPS: " << averageFPS << std::endl;

		frameCount = 0;
		totalTime = 0.0;
	}

	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}


void Window::onCreate() {}

void Window::onUpdate() {}

void Window::onDestroy()
{
	m_is_run = false;
}

