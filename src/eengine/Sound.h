#ifndef EENGINE_SOUND
#define EENGINE_SOUND

#include "Resource.h"

#include <stb_vorbis.c>

namespace eengine 
{
	class Sound : public Resource 
	{
		friend class Resources;

		char* m_rawData;

		void Load();

	public:
		~Sound();
	};
}

#endif