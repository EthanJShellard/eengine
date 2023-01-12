#include "AudioContext.h"

#include <stdexcept>

namespace eengine 
{
	void AudioContext::Initialise() 
	{
		// Get the first available device
		m_device = alcOpenDevice(nullptr);

		if (!m_device) 
		{
			throw std::runtime_error("Unable to open audio device...");
		}

		m_context = alcCreateContext(m_device, NULL);

		if (!m_context) 
		{
			alcCloseDevice(m_device);
			throw std::runtime_error("Unable to create openAL context with default device...");
		}

		if (!alcMakeContextCurrent(m_context)) 
		{
			alcDestroyContext(m_context);
			alcCloseDevice(m_device);
			throw std::runtime_error("Unable to set current openAL context...");
		}


	}
	
	AudioContext::AudioContext() :
		m_context(nullptr),
		m_device(nullptr)
	{}

	AudioContext::~AudioContext() 
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}
}