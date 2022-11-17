#ifndef EENGINE_AUDIO_SOURCE
#define EENGINE_AUDIO_SOURCE

#include "../eengine_defines.h"
#include "../Component.h"

#include <openAL/al.h>

namespace eengine 
{
	class Sound;

	COMPONENT(AudioSource)
	{
		ALuint m_id;

		shared<Transform> m_parentTransform;

		void OnInit();
		void OnTick();

	public:
		void PlayOneShot(std::shared_ptr<Sound> _sound);
	};
}

#endif // EENGINE_AUDIO_SOURCE