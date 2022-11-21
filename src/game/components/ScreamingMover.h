#include <eengine.h>

class ScreamingMover : public eengine::Component
{
	void OnTick();
	void OnBegin();

	shared<eengine::Sound> m_sound;
	shared<eengine::AudioSource> m_audioSource;
public:
	void OnInit();
};