#include "AudioListener.h"
#include "../Entity.h"
#include "../Camera.h"

namespace eengine 
{
	void AudioListener::OnInit() 
	{
		m_camTransform = GetCore()->GetMainCamera()->m_transform;
	}

	void AudioListener::OnTick(float _delatTime)
	{
		glm::vec3 camPos = m_camTransform->GetPosition();
		glm::vec3 camForward = m_camTransform->Forward();
		glm::vec3 camUp = m_camTransform->Up();

		ALfloat oValues[6] = {camForward.x, camForward.y, camForward.z, camUp.x, camUp.y, camUp.z};

		alListener3f(AL_POSITION, camPos.x, camPos.y, camPos.z);
		alListenerfv(AL_ORIENTATION, oValues);
	}
}
