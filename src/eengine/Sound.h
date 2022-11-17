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

		int m_channels;
		int m_sampleRate;

		void Load();

	public:
		ALuint GetID();
		int GetNumChannels();
		int GetSampleRate();

		Sound();
		~Sound();
	};
}

#endif