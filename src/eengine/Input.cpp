#include <SDL2/SDL.h>

#include "input.h"
#include "Core.h"
#include "Debug.h"

namespace eengine
{
	Input::Input() :
		m_quit(false),
		m_mouseSensitivity(0.25f),
		m_mouseDelta(0),
		m_mousePos(0),
		m_mouseScroll(0),
		m_updateCount(1),
		m_window(nullptr),
		m_mouse1State(false, 0),
		m_mouse2State(false, 0),
		m_mouse3State(false, 0)
	{
	}

	void Input::Update()
	{
		SDL_Event event = SDL_Event{ 0 };
		m_mouseDelta = glm::vec2(0, 0);
		m_mouseScroll = glm::vec2(0, 0);

		m_updateCount++;

		// We would rather overflow to 1 than 0. Maybe paranoid seeing as it would take ages to overflow this with a normal framerate.
		if (!m_updateCount) 
		{
			m_updateCount = 1;
			for (auto k : m_keys) 
			{
				k.second.lastUpdatePressed = 0;
				k.second.lastUpdateReleased = 0;
			}
		}

		// Update mouse position data via GetMouseState to circumvent jitter
		if (SDL_GetRelativeMouseMode()) 
		{
			int x(0), y(0);
			SDL_GetRelativeMouseState(&x, &y);
			m_mouseDelta = glm::vec2(x, y);

			SDL_GetMouseState(&x, &y);
			m_mousePos = glm::vec2(x, y);
		}
		else 
		{
			int x(0), y(0);
			SDL_GetMouseState(&x, &y);
			glm::vec2 newPos = glm::vec2(x, y);
			m_mouseDelta = newPos - m_mousePos;
			m_mousePos = newPos;
		}


		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				auto entry = m_keys.find(event.key.keysym.sym);
				if (entry == m_keys.end()) // Key is not yet present in map
				{
					// Insert key into the map for future reference!
					m_keys.insert(std::pair<int, KeyState>(event.key.keysym.sym, KeyState(true, m_updateCount)));
				}
				else
				{
					// Prevent multiple downs!
					if (!entry->second.down) 
					{
						entry->second.lastUpdatePressed = m_updateCount;
					}

					entry->second.down = true;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				auto entry = m_keys.find(event.key.keysym.sym);
				entry->second.down = false;
				entry->second.lastUpdateReleased = m_updateCount;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_mouse1State.down = true;
					m_mouse1State.lastUpdatePressed = m_updateCount;
					break;
				case SDL_BUTTON_RIGHT:
					m_mouse2State.down = true;
					m_mouse2State.lastUpdatePressed = m_updateCount;
					break;
				case SDL_BUTTON_MIDDLE:
					m_mouse2State.down = true;
					m_mouse2State.lastUpdatePressed = m_updateCount;
					break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_mouse1State.down = false;
					m_mouse1State.lastUpdateReleased = m_updateCount;
					break;
				case SDL_BUTTON_RIGHT:
					m_mouse2State.down = false;
					m_mouse2State.lastUpdateReleased = m_updateCount;
					break;
				case SDL_BUTTON_MIDDLE:
					m_mouse3State.down = false;
					m_mouse3State.lastUpdateReleased = m_updateCount;
					break;
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				m_mouseScroll.x = event.wheel.x;
				m_mouseScroll.y = event.wheel.y;
			}
			else if (event.type == SDL_QUIT)
			{
				m_quit = true;
			}
		}
	}

	bool Input::GetKey(KeyCode _key) const
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.down;
	}

	bool Input::GetKeyDown(KeyCode _key) const
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.lastUpdatePressed == m_updateCount;
	}

	bool Input::GetKeyUp(KeyCode _key) const
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.lastUpdateReleased == m_updateCount;
	}

	glm::vec2 Input::GetMouseDelta() const
	{
		return m_mouseDelta;
	}

	glm::vec2 Input::GetMouseWheelScroll() const
	{
		return m_mouseScroll;
	}

	bool Input::GetHasQuit() const
	{
		return m_quit;
	}

	float Input::GetMouseSensitivity() const
	{
		return m_mouseSensitivity;
	}

	void Input::SetMouseSensitivity(float _newSens)
	{
		m_mouseSensitivity = _newSens;
	}

	bool Input::GetMouse1() const
	{
		return m_mouse1State.down;
	}

	bool Input::GetMouse1Down() const 
	{
		return m_mouse1State.lastUpdatePressed == m_updateCount;
	}

	bool Input::GetMouse1Up() const 
	{
		return m_mouse1State.lastUpdateReleased == m_updateCount;
	}

	bool Input::GetMouse2() const
	{
		return m_mouse2State.down;
	}

	bool Input::GetMouse2Down() const
	{
		return m_mouse2State.lastUpdatePressed == m_updateCount;
	}

	bool Input::GetMouse2Up() const
	{
		return m_mouse2State.lastUpdateReleased == m_updateCount;
	}

	bool Input::GetMouse3() const
	{
		return m_mouse3State.down;
	}

	bool Input::GetMouse3Down() const
	{
		return m_mouse3State.lastUpdatePressed == m_updateCount;
	}

	bool Input::GetMouse3Up() const
	{
		return m_mouse3State.lastUpdateReleased == m_updateCount;
	}

	void Input::ResetMousePosition()
	{
		if (m_window) 
		{
			int width, height;
			SDL_GetWindowSize(m_window, &width, &height);
			SDL_WarpMouseInWindow(m_window, width / 2, height / 2);
		}
	}

	void Input::SetInputGrab(bool _lock) 
	{
		SDL_SetWindowGrab(m_window, (SDL_bool)_lock);
	}

	bool Input::GetInputGrab() const 
	{
		return SDL_GetWindowGrab(m_window);
	}

	void Input::SetRelativeMouseMode(bool _relativeMouseMode) const 
	{
		SDL_SetRelativeMouseMode((SDL_bool)_relativeMouseMode);
	}
}