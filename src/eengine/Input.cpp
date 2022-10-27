#include <SDL2/SDL.h>

#include "input.h"

namespace eengine
{
	Input::Input()
	{
		m_mouse1Pressed = false;
		m_mouse2Pressed = false;
		m_mouse3Pressed = false;
		m_quit = false;
		m_mouseSensitivity = 20.0f;
	}

	void Input::Update()
	{
		SDL_Event event = SDL_Event{ 0 };
		m_mouseDelta = glm::vec2(0, 0);
		m_mouseScroll = glm::vec2(0, 0);

		m_updateCount++;

		// We would rather overflow to 1 than 0. Maybe paranoid seeing as it would take years to overflow this with a normal framerate.
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
					entry->second.down = true;
					entry->second.lastUpdatePressed = m_updateCount;
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
				m_mouseDelta.x += event.motion.x - m_mousePreviousPos.x;
				m_mouseDelta.y += event.motion.y - m_mousePreviousPos.y;
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

		m_mousePreviousPos += m_mouseDelta;
	}

	bool Input::GetKey(KeyCode _key)
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.down;
	}

	bool Input::GetKeyDown(KeyCode _key) 
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.lastUpdatePressed == m_updateCount;
	}

	bool Input::GetKeyUp(KeyCode _key)
	{
		auto itr = m_keys.find(SDL_Keycode(_key));
		return itr == m_keys.end() ? false : itr->second.lastUpdateReleased == m_updateCount;
	}

	glm::vec2 Input::GetMouseDelta()
	{
		return m_mouseDelta;
	}

	glm::vec2 Input::GetMouseWheelScroll()
	{
		return m_mouseScroll;
	}

	bool Input::GetHasQuit()
	{
		return m_quit;
	}

	float Input::GetMouseSensitivity()
	{
		return m_mouseSensitivity;
	}

	void Input::SetMouseSensitivity(float _newSens)
	{
		m_mouseSensitivity = _newSens;
	}

	bool Input::Mouse1Down()
	{
		return m_mouse1Pressed;
	}

	bool Input::Mouse2Down()
	{
		return m_mouse2Pressed;
	}

	bool Input::Mouse3Down()
	{
		return m_mouse3Pressed;
	}

	void Input::ResetMousePosition(int _screenWidth, int _screenHeight)
	{
		m_mousePreviousPos = glm::vec2(_screenWidth / 2, _screenHeight / 2);
	}
}