#ifndef EENGINE_AUDIO_CONTEXT
#define EENGINE_AUDIO_CONTEXT

#include <AL/al.h>
#include <AL/alc.h>

#include "NonCopyable.h"

namespace eengine 
{
	/// @brief Contains audio context and devices.
	class AudioContext : public NonCopyable 
	{
		friend class Core;

		ALCdevice_struct* m_device;
		ALCcontext_struct* m_context;

		void Initialise();

		AudioContext();
	public:
		~AudioContext();
	};
}

#endif // EENGINE_AUDIO_CONTEXT