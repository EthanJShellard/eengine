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


void Suicider::OnTick() 
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

	if (GetCore()->GetInput()->GetKey(eengine::KeyCode::space)) 
	{
 		GetParent()->GetComponentOfType<eengine::RigidBody>()->ApplyImpulse(glm::vec3(0,1,0), glm::vec3(0,-1,0));
	}

	if (GetCore()->GetInput()->GetKey(eengine::KeyCode::right)) 
	{
		GetParent()->GetComponentOfType<eengine::RigidBody>()->ApplyTorque(glm::vec3(0,1,0));
	}
}