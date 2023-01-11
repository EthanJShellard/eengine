#ifndef EENGINE_SOUND
#define EENGINE_SOUND

#include "Resource.h"

#include <AL/al.h>

namespace eengine 
{
	class Sound : public Resource 
	{
		friend class Resources;

		ALuint m_id;

		int m_channels;
		int m_sampleRate;

		bool m_directional;
		bool m_dirty;
		bool m_loadedOnce;

		void Load();
		void PrepareBuffers();

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

		/// @brief Set whether or not this sound should use directional audio.
		/// @details If this is set to true, the sound will be buffered as mono regardless of the number of channels and directional audio will function,
		/// otherwise this sound can be stereo, if it has enough channels, but directional audio will not work.
		/// Changing this value will cause the sound to be reloaded and rebuffered if its ID has been accessed, so do it as infrequently as possible.
		/// @param _directional Whether or not this sound should use directional audio.
		void SetDirectional(bool _directional);

		/// @brief Get whether or not this sound is set to use directional audio.
		/// @details Sounds using directional audio cannot be buffered as stereo.
		/// @return Whether or not this sound is set to use directional audio.
		bool GetDirectional();



		Sound();
		~Sound();
	};
}

#endif