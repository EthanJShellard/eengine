#include <SDL2/SDL.h>

#include "Environment.h"

namespace eengine 
{
	Environment::Environment() 
	{
		m_lastTime = std::chrono::steady_clock::now();
		m_deltaTime = 0;
	}

	void Environment::OnFrameStart() 
	{
		auto time_now = std::chrono::steady_clock::now();
		std::chrono::duration<float, std::ratio<1, 1>> diff = time_now - m_lastTime;
		m_deltaTime = diff.count();
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