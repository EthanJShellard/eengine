#include "RigidBody.h"
#include "../Collider.h"

namespace eengine 
{
	void RigidBody::OnBegin() 
	{
		if (m_rigidBody != nullptr) 
		{
			// Register rigid body with physics context
		}
		else 
		{
			// Attempt to create bullet rigid body and register it with the physics context
		}
	}

	RigidBody::RigidBody(shared<Collider> _collider, btScalar _mass) 
	{
		btVector3 localInertia(0, 0, 0);

		// If mass isn't zero, rigidbody is dynamic
		if (_mass != 0.f) 
		{
			_collider->m_collisionShape->calculateLocalInertia(_mass, localInertia);
		}

		m_motionState = std::make_shared<btDefaultMotionState>(*(_collider->m_transform));
		btRigidBody::btRigidBodyConstructionInfo rbInfo(_mass, m_motionState.get(), _collider->m_collisionShape.get(), localInertia);
		m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
	}
}