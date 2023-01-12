#include "Environment.h"
#include "Debug.h"

#include <chrono>

namespace eengine 
{
	Environment::Environment() 
	{
		m_lastTime = std::chrono::high_resolution_clock::now();
		m_deltaTime = 0;
	}

	void Environment::OnFrameStart() 
	{
		auto timeNow = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> secs = timeNow - m_lastTime;
		m_lastTime = timeNow;
		m_deltaTime = secs.count();
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