#include <SDL2/SDL.h>

#include "Environment.h"

namespace eengine 
{
	Environment::Environment() 
	{
		m_lastTime = SDL_GetTicks();
		m_deltaTime = 0;
	}

	void Environment::OnFrameStart() 
	{
		uint32_t time_now = SDL_GetTicks();
		uint32_t diff = time_now - m_lastTime;
		m_deltaTime = diff / 1000.0f;
		m_lastTime = time_now;
	}

	float Environment::GetDeltaTime() 
	{
		return m_deltaTime;
	}

	std::string Environment::GetProjectWorkingDirectory() 
	{
		return m_projectWorkingDirectory;
	}
}