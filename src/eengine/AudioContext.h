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
	};
}