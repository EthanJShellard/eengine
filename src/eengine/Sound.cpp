#include "Sound.h"

#include <stb_vorbis.c>

#include <vector>

namespace eengine 
{
	void Sound::Load() 
	{
		int error = 0;
		short* alloc_buffer;

		//stb_vorbis_open_filename(m_path.c_str(), &error, &alloc_buffer);
		size_t len = stb_vorbis_decode_filename(m_path.c_str(), &m_channels, &m_sampleRate, &alloc_buffer);

		std::vector<unsigned char> buffer;
		buffer.resize(len * m_channels * sizeof(short));
		memcpy(&buffer.at(0), alloc_buffer, buffer.size());

		alGenBuffers(1, &m_id);

		ALenum format = AL_FORMAT_MONO16;

		// Expecting 16bit from stb_vorbis
		if (m_channels == 1) 
		{
			format = AL_FORMAT_MONO16;
		}
		else if (m_channels == 2)
		{
			m_sampleRate *= 2;
		}

		alBufferData(m_id, format, &buffer.at(0), ALsizei(buffer.size()), m_sampleRate);

		// STB vorbis uses ?
		free(alloc_buffer);
	}

	ALuint Sound::GetID() 
	{
		return m_id;
	}

	int Sound::GetNumChannels() 
	{
		return m_channels;
	}

	int Sound::GetSampleRate() 
	{
		return m_sampleRate;
	}

	Sound::Sound() :
		m_id(-1),
		m_channels(-1),
		m_sampleRate(-1)
	{	
	}

	Sound::~Sound() 
	{
		alDeleteBuffers(1, &m_id);
	}
}