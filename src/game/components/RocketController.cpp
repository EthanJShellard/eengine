#include "RocketController.h"
#include "PlayerController.h"
#include "Explosion.h"


RocketController::RocketController(float _maxTime) :
	m_timer(0.0f),
	m_maxTime(_maxTime),
	m_explosionDamage(1.0f),
	m_explosionForce(10.0f),
	m_explosionRange(1.0f)
{
}

void RocketController::Explode() 
{
	auto explosion = GetCore()->AddEntity();
	auto as = explosion->AddComponent<eengine::AudioSource>();
	as->SetLooping(false);
	as->SetVolume(0.5f);
	as->PlayOneShot(m_explosionSound);
	explosion->AddComponent<Explosion>(1.0f, 12.0f, 3.0f);
	auto trigger = explosion->AddComponent<eengine::RigidBody>(std::make_shared<eengine::SphereCollider>(m_explosionRange), 1.0f);
	trigger->SetIsTrigger(true);
	trigger->SetIsStatic(true);
	explosion->AddComponent<eengine::ModelRenderer>("/data/models/explosion/explosion.obj");
	explosion->GetTransform()->SetPosition(GetParent()->GetTransform()->GetPosition());

	m_timer = 0.0f;
	GetParent()->Disable();
}

void RocketController::OnBegin() 
{
	m_explosionSound = GetCore()->GetResources()->Load<eengine::Sound>("/data/audio/rocket/explosion.ogg");
	m_explosionSound->SetDirectional(true);
}

void RocketController::OnTick(float _deltaTime) 
{
	m_timer += _deltaTime;
	if (m_timer >= m_maxTime) 
	{
		Explode();
	}
}

void RocketController::OnTriggerEnter(shared<eengine::RigidBody> _other) 
{
	if (_other->GetParent()->GetComponentOfType<PlayerController>() == nullptr) 
	{
		Explode();
	}
}