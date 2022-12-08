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

	void AudioSource::OnTick(float _deltaTime) 
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
		// Detach source so we properly release any previously playing sounds.
		// OpenAL will not dispose of buffer memory properly is we do not detach the buffer in this case.
		if (_sound == m_currentSound) 
		{
			alSourcei(m_id, AL_BUFFER, 0);
		}
		else 
		{
			m_currentSound = _sound;
		}

		alSourcei(m_id, AL_BUFFER, _sound->GetID());
		alListener3f(AL_POSITION, 0,0,0);
		alSourcei(m_id, AL_LOOPING, m_loop);
		alSourcef(m_id, AL_GAIN, m_volume);
		alSourcef(m_id, AL_PITCH, m_pitch);
		alSourcePlay(m_id);

		m_currentSound = _sound;
	}

	void AudioSource::Stop(bool _detachSource) 
	{
		alSourceStop(m_id);
		if (_detachSource) 
		{
			alSourcei(m_id, AL_BUFFER, 0);
			m_currentSound = nullptr;
		} 
	}

	AudioSource::~AudioSource() 
	{
		alSourceStop(m_id);
		alDeleteSources(1, &m_id);
	}
}