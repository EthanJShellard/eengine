#include "WeaponPickup.h"
#include "PlayerController.h"

WeaponPickup::WeaponPickup(float _bobDistance, float _bobSpeed, float _rotationSpeed) :
	m_bobDistance(_bobDistance),
	m_bobSpeed(_bobSpeed),
	m_rotationSpeed(_rotationSpeed),
	m_startingHeight(0),
	m_bobProgress(0)
{
	
}

void WeaponPickup::OnBegin() 
{
	m_transform = GetParent()->GetTransform();
	m_startingHeight = m_transform->GetPosition().y;
}

void WeaponPickup::OnTick(float _deltaTime) 
{
	m_bobProgress += _deltaTime * m_bobSpeed;

	auto pos = m_transform->GetPosition();
	pos.y = m_startingHeight + glm::sin(glm::radians(m_bobProgress)) * m_bobDistance;

	m_transform->SetPosition(pos);
	m_transform->Rotate(_deltaTime * m_rotationSpeed, glm::vec3(0,1,0));
}

void WeaponPickup::OnTriggerEnter(shared<eengine::RigidBody> _other) 
{
	auto pc = _other->GetParent()->GetComponentsOfType<PlayerController>();
	if (pc.size()) 
	{
		pc.at(0)->GiveWeapon();
		GetParent()->Destroy();
	}
}