#include "AudioListener.h"
#include "../Entity.h"

namespace eengine 
{
	void AudioListener::OnInit(float _delatTime) 
	{
		m_parentTransform = GetParent()->GetTransform();
	}

	void AudioListener::OnTick() 
	{
		glm::vec3 parentPos = m_parentTransform->GetPosition();

		alListener3f(AL_POSITION, parentPos.x, parentPos.y, parentPos.z);
	}
}
