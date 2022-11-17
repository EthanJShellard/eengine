#include "AudioSource.h"
#include "../Entity.h"
#include "../Sound.h"

namespace eengine 
{
	void AudioSource::OnInit() 
	{
		alGenSources(1, &m_id);

		m_parentTransform = GetParent()->GetTransform();

		m_pitch = 1.0f;
		m_volume = 1.0f;
		m_loop = false;
	}

	void AudioSource::OnTick() 
	{
		glm::vec3 parentPos = m_parentTransform->GetPosition();

		alSource3f(m_id, AL_POSITION, parentPos.x, parentPos.y, parentPos.z);
	}

	bool AudioSource::IsPlaying() 
	{
		ALenum state;
		alGetSourcei(m_id, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	void AudioSource::PlayOneShot(std::shared_ptr<Sound> _sound) 
	{
		alSourcei(m_id, AL_BUFFER, _sound->GetID());
		alListener3f(AL_POSITION, 0,0,0);
		alSourcei(m_id, AL_LOOPING, m_loop);
		alSourcef(m_id, AL_GAIN, m_volume);
		alSourcef(m_id, AL_PITCH, m_pitch);
		alSourcePlay(m_id);
	}
}