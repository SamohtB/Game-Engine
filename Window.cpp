#include "Window.h"
#include "EngineTime.h"
#include <iostream>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
    {
        return true;
    }

	switch (msg)
	{
		case WM_CREATE:
		{
			break;
		}

		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if(window) window->onFocus();
			break;
		}

		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onKillFocus();
			break;
		}

		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window() 
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
		throw std::exception("WindowRegistration was not successful");
	}

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
		"MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		1024, 768, NULL, NULL, NULL, NULL);

	//Create Window
	if (!m_hwnd)
	{
		throw std::exception("WindowCreation was not successful");
	}

	//Show Window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;
}

Window::~Window()
{
	if (!::DestroyWindow(m_hwnd))
	{
		std::cerr << "Window was not destroyed successfully";
	}
}

bool Window::broadcast()
{
	if (!this->isInit)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();
		this->isInit = true;
	}

	EngineTime::LogFrameStart();
	this->onUpdate();
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	EngineTime::LogFrameEnd();

	frameCount++;
	totalTime += EngineTime::sharedInstance->deltaTime;

	if (totalTime >= updateInterval)
	{
		double averageFPS = frameCount / totalTime;

		frameCount = 0;
		totalTime = 0.0;
	}

	return true;
}

bool Window::isRun()
{
	if(m_is_run) broadcast();
	return m_is_run;
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

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

