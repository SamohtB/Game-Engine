#pragma once
#include <Windows.h>
#include <unordered_map>

class Window
{
public:
	Window();
	~Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	bool isKeyPressed(WPARAM key);
	void setKeyPressed(WPARAM key, bool pressed);

	bool isBackspace() const { return isBackspacePressed; }
	bool isDelete() const { return isDeletePressed; }
	bool isSpace() const { return isSpacePressed; }

	void setBackspace(bool value) { isBackspacePressed = value; }
	void setDelete(bool value) { isDeletePressed = value; }
	void setSpace(bool value) { isSpacePressed = value; }

protected:
	HWND m_hwnd = {};
	bool m_is_run = false;

private:
	std::unordered_map<WPARAM, bool> keyStates;
	bool isBackspacePressed = false;
	bool isDeletePressed = false;
	bool isSpacePressed = false;
};