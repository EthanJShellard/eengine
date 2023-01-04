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
	//if (m_count == m_target)
	//{
	//	GetParent()->Destroy();
	//}
	//else 
	//{
	//	m_count++;
	//	std::cout << "Hello!" << std::endl;
	//}

	auto input = GetCore()->GetInput();

	if (input->GetKeyDown(eengine::KeyCode::space)) 
	{
 		GetParent()->GetComponentOfType<eengine::RigidBody>()->ApplyImpulse(glm::vec3(0,5,0), glm::vec3(0,-1,0));
	}

	if (input->GetKey(eengine::KeyCode::right)) 
	{
		GetParent()->GetComponentOfType<eengine::RigidBody>()->ApplyTorque(glm::vec3(0,1,0));
	}

	if (input->GetKeyDown(eengine::KeyCode::j)) 
	{
		GetParent()->GetTransform()->Translate(glm::vec3(0,1.0,0));
	}

	auto delta = input->GetMouseDelta();


	//eengine::Debug::Log("mouse delta: (" + std::to_string(delta.x) + ", " + std::to_string(delta.y) + ")");

	float sensitivity = input->GetMouseSensitivity();
	auto transform = GetCore()->GetMainCamera()->m_transform;

	transform->Rotate(_deltaTime * -sensitivity * delta.x, glm::vec3(0,1,0));
	transform->Rotate(_deltaTime * -sensitivity * delta.y, transform->Right());

	if (input->GetKey(eengine::KeyCode::w)) 
	{
		transform->Translate(5 * _deltaTime * -transform->Forward());
	}
	if (input->GetKey(eengine::KeyCode::s))
	{
		transform->Translate(5 * _deltaTime * transform->Forward());
	}
	if (input->GetKey(eengine::KeyCode::a))
	{
		transform->Translate(5 * _deltaTime * -transform->Right());
	}
	if (input->GetKey(eengine::KeyCode::d))
	{
		transform->Translate(5 * _deltaTime * transform->Right());
	}
	if (input->GetKey(eengine::KeyCode::escape)) 
	{
		GetCore()->Stop();
	}
}