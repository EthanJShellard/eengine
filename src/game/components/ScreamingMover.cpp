#include "ScreamingMover.h"
#include <Environment.h>

#include <stdexcept>

void ScreamingMover::OnInit() 
{
	m_sound = GetCore()->GetResources()->Load<eengine::Sound>("\\data\\audio\\dixie_horn.ogg");
}

void ScreamingMover::OnTick() 
{
	// Really bad way of doing this, but don't have OnStart implemented yet
	if (!m_audioSource) 
	{
		m_audioSource = GetParent()->GetComponentOfType<eengine::AudioSource>();
		m_audioSource->SetVolume(0.5f);
		m_audioSource->SetLooping(true);
	}

	// Again, because I don't have OnStart
	if (!m_audioSource->IsPlaying())
	{
		m_audioSource->PlayOneShot(m_sound);
	}

	glm::vec3 movement = glm::vec3(0);
	if (GetInput()->GetKey(eengine::KeyCode::w)) 
	{
		movement += glm::vec3(0,0,-5);
	}
	if (GetInput()->GetKey(eengine::KeyCode::a))
	{
		movement += glm::vec3(-5, 0, 0);
	}
	if (GetInput()->GetKey(eengine::KeyCode::d))
	{
		movement += glm::vec3(5, 0, 0);
	}
	if (GetInput()->GetKey(eengine::KeyCode::s))
	{
		movement += glm::vec3(0, 0, 5);
	}
	GetParent()->GetTransform()->Translate(movement * 5.0f * GetCore()->GetEnvironment()->GetDeltaTime());

}