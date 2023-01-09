#include <iostream>

#include "Suicider.h"

Suicider::Suicider() 
{
	m_target = 10;
	m_count = 0;
}

Suicider::Suicider(int _target) 
{
	m_target = _target;
	m_count = 0;
}


void Suicider::OnTick(float _deltaTime) 
{
}

void Suicider::OnTriggerEnter(shared<eengine::RigidBody> _other) 
{
	GetParent()->GetComponentOfType<eengine::AudioSource>()->PlayOneShot(GetCore()->GetResources()->Load<eengine::Sound>("/data/audio/91962__billengholm-yahoo-com__ridebell.ogg"));
	auto parentPos = _other->GetParent()->GetTransform()->GetPosition();
	eengine::Debug::Log("Entered rigidbody with centre: (" + std::to_string(parentPos.x) + ", " + std::to_string(parentPos.y) + ", " + std::to_string(parentPos.z) + ")");
}

void Suicider::OnTriggerExit(shared<eengine::RigidBody> _other) 
{
	auto parentPos = _other->GetParent()->GetTransform()->GetPosition();
	eengine::Debug::Log("Exited rigidbody with centre: (" + std::to_string(parentPos.x) + ", " + std::to_string(parentPos.y) + ", " + std::to_string(parentPos.z) + ")");
}

void Suicider::OnCollisionEnter(shared<eengine::RigidBody> _other) 
{
	eengine::Debug::Log("Collision entered!");
}

void Suicider::OnCollisionExit(shared<eengine::RigidBody> _other) 
{
	eengine::Debug::Log("Collision exited!");
}