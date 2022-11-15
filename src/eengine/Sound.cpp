#include "Sound.h"



namespace eengine 
{
	void Sound::Load() 
	{
		int error = 0;
		stb_vorbis_alloc alloc_buffer;

		stb_vorbis_open_filename(m_path.c_str(), &error, &alloc_buffer);

		m_rawData = alloc_buffer.alloc_buffer;
	}

	Sound::~Sound() 
	{
		free(m_rawData);
	}
}