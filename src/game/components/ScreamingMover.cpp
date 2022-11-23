#include "ScreamingMover.h"
#include <Environment.h>

#include <stdexcept>

void ScreamingMover::OnInit() 
{
	m_sound = GetCore()->GetResources()->Load<eengine::Sound>("\\data\\audio\\dixie_horn.ogg");
	m_secondSound = GetCore()->GetResources()->Load<eengine::Sound>("\\data\\audio\\91962__billengholm-yahoo-com__ridebell.ogg");
}

void ScreamingMover::OnTick() 
{
	// Really bad way of doing this, but don't have OnStart implemented yet
	if (!m_audioSource) 
	{
		m_audioSource = GetParent()->GetComponentOfType<eengine::AudioSource>();
		m_audioSource->SetVolume(0.1f);
		//m_audioSource->SetLooping(true);
	}

	// Again, because I don't have OnStart
	if (!m_audioSource->IsPlaying())
	{
		bool dir = !m_sound->GetDirectional();
		m_audioSource->PlayOneShot(dir ? m_sound : m_secondSound);
		m_sound->SetDirectional(dir);
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

void ScreamingMover::OnBegin() 
{
	eengine::Debug::Log("Began!");
}