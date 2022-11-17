#ifndef EENGINE_AUDIO_LISTENER
#define EENGINE_AUDIO_LISTENER

#include "../eengine_defines.h"
#include "../Component.h"

#include <openAL/al.h>

namespace eengine 
{
	COMPONENT(AudioListener)
	{
		shared<Transform> m_parentTransform;

		void OnInit();
		void OnTick();
	};
}

#endif // EENGINE_AUDIO_LISTENER