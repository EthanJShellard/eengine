#ifndef EENGINE_AUDIO_SOURCE
#define EENGINE_AUDIO_SOURCE

#include "../eengine_defines.h"
#include "../Component.h"

#include <AL/al.h>

namespace eengine 
{
	class Sound;

	/// @brief A source of audio which has adjustable volume, pitch, and other properties used for audio playback.
	class AudioSource : public Component
	{
		ALuint m_id;
		shared<Sound> m_currentSound;
		float m_volume;
		float m_pitch;
		bool m_loop;

		shared<Transform> m_parentTransform;

		void OnTick(float _deltaTime);
		void OnDisable();
		void OnEnable();

	public:
		/// @brief Called by the engine when this component is first initialised. Do not call this unless you are certain of what you are doing.
		void OnInit();

		/// @brief Get whether or not this source is currently playing any audio.
		/// @return True if this source is currently playing audio.
		bool IsPlaying();

		/// @brief Play a sound now. Will loop if this audio source is set to loop.
		/// @param _sound The sound to be played.
		void PlayOneShot(std::shared_ptr<Sound> _sound);

		/// @brief Set the new volume of this audio source.
		/// @param _newVolume The new volume, expected to be a real number where 1.0 is unadjusted.
		void SetVolume(float _newVolume) { m_volume = _newVolume; }

		/// @brief Get the current volume of this audio source.
		/// @return The current volume of this audio source as a real number where 1.0 is unadjusted.
		float GetVolume() { return m_volume; }

		/// @brief Set the new pitch of this audio source.
		/// @param _newPitch The new pitch, expected to be a real number where 1.0 is unadjusted.
		void SetPitch(float _newPitch) { m_pitch = _newPitch; }

		/// @brief Get the current pitch of this audio source.
		/// @return The current pitch of this audio source as a real number where 1.0 is unadjusted.
		float GetPitch() { return m_pitch; }

		/// @brief Set whether or not this audio source should loop when the sound it is playing ends.
		/// @param _loop Whether or not this audio source should loop.
		void SetLooping(bool _loop) { m_loop = _loop; }

		/// @brief Get whether or not this audio source is set to loop when the sound it is playing ends.
		/// @return Whether or not this audio source will loop.
		bool GetLooping() { return m_loop; }

		/// @brief Stop playback from this audio source.
		/// @param _detachSource Whether or not to detach the currently played sound from this source.
		void Stop(bool _detachSound = true);

		~AudioSource();
	};
}

#endif // EENGINE_AUDIO_SOURCE