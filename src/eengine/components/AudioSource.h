#ifndef EENGINE_AUDIO_SOURCE
#define EENGINE_AUDIO_SOURCE

#include "../eengine_defines.h"
#include "../Component.h"

#include <openAL/al.h>

namespace eengine 
{
	class Sound;

	class AudioSource : public Component
	{
		ALuint m_id;
		float m_volume;
		float m_pitch;
		bool m_loop;

		shared<Transform> m_parentTransform;

		void OnTick();

	public:
		void OnInit();
		bool IsPlaying();

		void PlayOneShot(std::shared_ptr<Sound> _sound);

		void SetVolume(float _newVolume) { m_volume = _newVolume; }
		float GetVolume() { return m_volume; }

		void SetPitch(float _newPitch) { m_pitch = _newPitch; }
		float GetPitch() { return m_pitch; }

		void SetLooping(bool _loop) { m_loop = _loop; }
		bool GetLooping() { return m_loop; }
	};
}

#endif // EENGINE_AUDIO_SOURCE