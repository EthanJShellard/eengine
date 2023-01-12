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
		shared<Transform> m_camTransform;

		void OnTick(float _deltaTime);

	public:
		/// @brief Called by the engine when this component is first initialised. Do not call this unless you are certain of what you are doing. 
		void OnInit();
	};
}

#endif // EENGINE_AUDIO_LISTENER