#include <SDL2/SDL.h>

#include "input.h"
#include "Core.h"
#include "Debug.h"

namespace eengine
{
	Input::Input() :
		m_mouse1Pressed(false),
		m_mouse2Pressed(false),
		m_mouse3Pressed(false),
		m_quit(false),
		m_mouseSensitivity(12.0f),
		m_mouseDelta(0),
		m_mousePos(0),
		m_mouseScroll(0),
		m_updateCount(1),
		m_window(nullptr)
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
			else if (event.type == SDL_MOUSEMOTION)
			{
				// use += delta to avoid issues if mouse motion comes in more than once
				bool relativeMode = SDL_GetRelativeMouseMode();
				m_mouseDelta.x += relativeMode ? event.motion.xrel : event.motion.x - m_mousePos.x;
				m_mouseDelta.y += relativeMode ? event.motion.yrel : event.motion.y - m_mousePos.y;
				m_mousePos.x = event.motion.x;
				m_mousePos.y = event.motion.y;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_mouse1Pressed = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_mouse2Pressed = true;
					break;
				case SDL_BUTTON_MIDDLE:
					m_mouse3Pressed = true;
					break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_mouse1Pressed = false;
					break;
				case SDL_BUTTON_RIGHT:
					m_mouse2Pressed = false;
					break;
				case SDL_BUTTON_MIDDLE:
					m_mouse3Pressed = false;
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

	bool Input::Mouse1Down() const
	{
		return m_mouse1Pressed;
	}

	bool Input::Mouse2Down() const
	{
		return m_mouse2Pressed;
	}

	bool Input::Mouse3Down() const
	{
		return m_mouse3Pressed;
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