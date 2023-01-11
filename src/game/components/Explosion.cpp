#include "Explosion.h"


void Explosion::OnBegin() 
{
	// Apply forces
	m_renderer = GetParent()->GetComponentOfType<eengine::ModelRenderer>();
}

void Explosion::OnTick(float _deltaTime) 
{
	m_timer += _deltaTime;
	
	m_renderer->SetAlpha(((m_timeToDecay - m_timer) / m_timeToDecay));

	if (m_timer > m_timeToDecay)
	{
		GetParent()->Destroy();
	}
	else if (m_timer > GetCore()->GetPhysicsContext()->GetFixedTimeStep()) 
	{
		m_updateWaited = true;
	}
}

void Explosion::OnLateTick(float _deltaTime) 
{
	if (m_updateWaited) 
	{
		GetParent()->GetComponentOfType<eengine::RigidBody>()->SetIsEnabled(false);
	}
}

void Explosion::OnTriggerEnter(shared<eengine::RigidBody> _other) 
{
	glm::vec3 displacement = _other->GetParent()->GetTransform()->GetPosition() - GetParent()->GetTransform()->GetPosition();
	_other->ApplyImpulse(glm::normalize(displacement) * m_force, -displacement);
	m_updateWaited = true;
}

Explosion::Explosion(float _range, float _force, float _decayTime) :
	m_range(_range),
	m_force(_force),
	m_timeToDecay(_decayTime),
	m_timer(0.0f),
	m_updateWaited(false)
{
}