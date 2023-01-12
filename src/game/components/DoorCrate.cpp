#include "DoorCrate.h"
#include "RocketController.h"

void DoorCrate::OnCollisionEnter(shared<eengine::RigidBody> _other) 
{
	if (_other->GetParent()->GetComponentOfType<RocketController>()) 
	{
		GetParent()->Destroy();
	}
}