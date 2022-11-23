#include "Sound.h"

#include <stb_vorbis.c>

#include <vector>

namespace eengine 
{
	void Sound::Load() 
	{
		m_dirty = true;
	}

	void Sound::PrepareBuffers() 
	{
		alDeleteBuffers(1, &m_id);

		int error = 0;
		short* alloc_buffer;

		//stb_vorbis_open_filename(m_path.c_str(), &error, &alloc_buffer);
		size_t len = stb_vorbis_decode_filename(m_path.c_str(), &m_channels, &m_sampleRate, &alloc_buffer);

		std::vector<unsigned char> buffer;
		buffer.resize(len * m_channels * sizeof(short));
		memcpy(&buffer.at(0), alloc_buffer, buffer.size());

		alGenBuffers(1, &m_id);

		// Expecting 16bit from stb_vorbis
		ALenum format = AL_FORMAT_MONO16;
		
		if (m_channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		if (m_channels == 2)
		{
			if (m_directional) 
			{
				// If we want directional audio for this sound, stick with mono regardless and adjust sample rate accordingly.
				m_sampleRate *= 2;
			}
			else 
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(m_id, format, &buffer.at(0), ALsizei(buffer.size()), m_sampleRate);

		// STB vorbis uses ?
		free(alloc_buffer);
	}

	ALuint Sound::GetID() 
	{
		if (m_dirty) 
		{
			PrepareBuffers();
		}
		return m_id;
	}

	int Sound::GetNumChannels() 
	{
		if (m_dirty)
		{
			PrepareBuffers();
		}
		return m_channels;
	}

	int Sound::GetSampleRate() 
	{
		if (m_dirty)
		{
			PrepareBuffers();
		}
		return m_sampleRate;
	}

	void Sound::SetDirectional(bool _directional) 
	{
		m_directional = _directional;
		m_dirty = true;
	}
	
	bool Sound::GetDirectional() 
	{
		return m_directional;
	}

	Sound::Sound() :
		m_id(-1),
		m_channels(-1),
		m_sampleRate(-1),
		m_dirty(false),
		m_directional(true)
	{	
	}

	Sound::~Sound() 
	{
		alDeleteBuffers(1, &m_id);
	}
}