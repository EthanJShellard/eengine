#ifndef EENGINE_AUDIO_LISTENER
#define EENGINE_AUDIO_LISTENER

#include "../eengine_defines.h"
#include "../Component.h"

#include <AL/al.h>

namespace eengine 
{
	/// @brief Represents the location and properties of an audio listener. You should only have one of these active at a time.
	class AudioListener : public Component
	{
		shared<Transform> m_parentTransform;

		void OnInit();
		void OnTick();
	};
}

#endif // EENGINE_AUDIO_LISTENER