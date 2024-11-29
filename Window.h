#pragma once
#include <Windows.h>
#include <unordered_map>

class Window
{
public:
	Window();
	~Window();
	
	bool isRun();

	RECT getClientWindowRect();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

protected:
	HWND m_hwnd = {};
	bool m_is_run = false;

private:
	bool broadcast();

	int frameCount = 0;
	double totalTime = 0.0;
	double updateInterval = 1.0;
	bool isInit = false;
};
