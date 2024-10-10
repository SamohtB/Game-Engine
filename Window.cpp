#include "Window.h"
#include "EngineTime.h"

Window::Window() {}

Window::~Window(){}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static bool isEscapePressed = false;
	static bool isBackspacePressed = false;
	static bool isDeletePressed = false;
	static bool isSpacePressed = false;

	Window* win = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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
		switch (wparam)
		{
		case VK_ESCAPE:
			win->onDestroy();
			::PostQuitMessage(1);
			break;
		case VK_BACK:
			win->isBackspacePressed = true;
			break;
		case VK_DELETE:
			win->isDeletePressed = true;
			break;
		case VK_SPACE:
			win->isSpacePressed = true;
			break;
		}
		break;
	}

	case WM_KEYUP:
	{
		switch (wparam)
		{
		case VK_BACK:
			win->isBackspacePressed = false;
			break;
		case VK_DELETE:
			win->isDeletePressed = false;
			break;
		case VK_SPACE:
			win->isSpacePressed = false;
			break;
		}
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

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

	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

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

