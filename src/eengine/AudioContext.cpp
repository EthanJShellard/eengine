#include "AudioContext.h"

namespace eengine 
{
	void AudioContext::Initialise() 
	{
		// Get the first available device
		m_device = alcOpenDevice(nullptr);

		if (m_device) 
		{
			//m_context = alcCreateContext(m_device, nullptr);
			//alcMakeContextCurrent(m_context);
		}
	}
}