#include "RocketController.h"
#include "PlayerController.h"


RocketController::RocketController(float _maxTime) :
	m_timer(0.0f),
	m_maxTime(_maxTime)
{
}

void RocketController::Explode() 
{
	m_timer = 0.0f;
	GetParent()->Disable();
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
	if (!_other->GetParent()->HasComponentOfType<PlayerController>()) 
	{
		Explode();
	}
}