#include "Sound.h"

#include <stb_vorbis.c>

#include <vector>

namespace eengine 
{
	void Sound::Load() 
	{
		int error = 0;
		stb_vorbis_alloc alloc_buffer;

		stb_vorbis_open_filename(m_path.c_str(), &error, &alloc_buffer);

		std::vector<char> bufferData;
		
		char* rawData = alloc_buffer.alloc_buffer;

		alGenBuffers(1, &m_id);

		ALenum format = 0;
		ALsizei freq = 0;

		alBufferData(m_id, format, &rawData, static_cast<ALsizei>(alloc_buffer.alloc_buffer_length_in_bytes), freq);

		// STB vorbis uses 
		free(rawData);
	}

	ALuint Sound::GetID() 
	{
		return m_id;
	}

	Sound::~Sound() 
	{
		alDeleteBuffers(1, &m_id);
	}
}