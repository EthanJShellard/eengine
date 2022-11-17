#ifndef EENGINE_SOUND
#define EENGINE_SOUND

#include "Resource.h"

#include <openAL/al.h>

namespace eengine 
{
	class Sound : public Resource 
	{
		friend class Resources;

		ALuint m_id;

		void Load();

	public:
		ALuint GetID();

		~Sound();
	};
}

#endif