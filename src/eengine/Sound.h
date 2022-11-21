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
		/// @brief Get the the ID of this Sound.
		/// @return This Sound's ID.
		ALuint GetID();

		/// @brief Get the number of audio channels this sound has.
		/// @return The number audio channels this sound has.
		int GetNumChannels();

		/// @brief Get the sample rate of this sound in Hz.
		/// @return The sample rate of this sound in Hz.
		int GetSampleRate();

		Sound();
		~Sound();
	};
}

#endif