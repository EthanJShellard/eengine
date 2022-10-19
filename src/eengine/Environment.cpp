#include <SDL2/SDL.h>

#include "Environment.h"

namespace eengine 
{
	Environment::Environment() 
	{
		m_lastTime = 0;
		m_deltaTime = 0;
	}

	void Environment::OnFrameStart() 
	{
		GLuint time = SDL_GetTicks();
		GLuint diff = time - m_lastTime;
		m_deltaTime = diff / 1000.0f;
		m_lastTime = time;
	}

	float Environment::GetDeltaTime() 
	{
		return m_deltaTime;
	}
}