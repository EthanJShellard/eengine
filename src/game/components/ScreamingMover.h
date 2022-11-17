#include <eengine.h>

COMPONENT(ScreamingMover)
{
	void OnTick();

	shared<eengine::Sound> m_sound;
	shared<eengine::AudioSource> m_audioSource;
public:
	void OnInit();
};