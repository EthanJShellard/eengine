#ifndef EENGINE_AUDIO_CONTEXT
#define EENGINE_AUDIO_CONTEXT

#include <openAL/al.h>
#include <openAL/alc.h>

#include "NonCopyable.h"

namespace eengine 
{
	class AudioContext : public NonCopyable 
	{
		ALCdevice_struct* m_device;
		ALCcontext_struct* m_context;

		void Initialise();

	public:
		~AudioContext();
	};
}

#endif // EENGINE_AUDIO_CONTEXT