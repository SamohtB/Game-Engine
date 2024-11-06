#include "InputSystem.h"
#include "Windows.h"

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	delete sharedInstance;
}

void InputSystem::update()
{
	 XMVECTOR current_mouse_pos = getMousePosition();

	 if (first_time)
	 {
		 first_time = false;
		 old_mouse_position = current_mouse_pos;
	 }

	if (!XMVector2Equal(current_mouse_pos, old_mouse_position))
	{
		/* Mouse Move Event */
		std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

		while (it != m_map_listeners.end())
		{
			it->second->onMouseMove(XMVectorSubtract(current_mouse_pos, old_mouse_position));
			it++;
		}

		old_mouse_position = current_mouse_pos;
	}

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			/* Key Down */
			if (m_keys_state[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

				while (it != m_map_listeners.end())
				{

					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onLeftMouseDown(current_mouse_pos);
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onRightMouseDown(current_mouse_pos);
						}
					}
					else
					{
						it->second->onKeyDown(i);
					}
					
					it++;
				}
			}
			/* Key Up */
			else
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

					while (it != m_map_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							it->second->onLeftMouseUp(current_mouse_pos);
						}
						else if (i == VK_RBUTTON)
						{
							it->second->onRightMouseUp(current_mouse_pos);
						}
						else
						{
							it->second->onKeyUp(i);
						}

						it++;
					}
				}
			}
		}

		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_map_listeners.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.find(listener);

	if(it != m_map_listeners.end())
	{
		m_map_listeners.erase(it);
	}
}

XMVECTOR InputSystem::getMousePosition()
{
	POINT point;
	if (::GetCursorPos(&point))
	{
		return DirectX::XMVectorSet(static_cast<float>(point.x), static_cast<float>(point.y), 0.0f, 0.0f);
	}
	else
	{
		return DirectX::XMVectorZero();
	}
}

InputSystem::InputSystem() {}

InputSystem::~InputSystem() {}