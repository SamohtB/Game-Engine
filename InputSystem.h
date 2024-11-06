#pragma once
#include "InputListener.h"
#include <map>

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const XMFLOAT2& point);
	void showCursor(bool show);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {}
	InputSystem& operator=(InputSystem const&) {}

	static InputSystem* sharedInstance;

	std::map<InputListener*, InputListener*> m_map_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	XMVECTOR old_mouse_position = XMVectorZero();
	bool first_time = true;

	XMVECTOR getMousePosition();
};

