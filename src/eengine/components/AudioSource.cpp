#include "AudioSource.h"
#include "../Entity.h"
#include "../Sound.h"

namespace eengine 
{
	void AudioSource::OnInit() 
	{
		alGenSources(1, &m_id);

		m_parentTransform = GetParent()->GetTransform();
	}

	void AudioSource::OnTick() 
	{
		glm::vec3 parentPos = m_parentTransform->GetPosition();

		alSource3f(m_id, AL_POSITION, parentPos.x, parentPos.y, parentPos.z);
	}

	void AudioSource::PlayOneShot(std::shared_ptr<Sound> _sound) 
	{
		alSourcei(m_id, AL_BUFFER, _sound->GetID());
		alSourcePlay(m_id);
	}
}