#include "RigidBody.h"
#include "../Collider.h"
#include "../Core.h"
#include "../PhysicsContext.h"
#include "../Entity.h"

namespace eengine 
{
	void RigidBody::OnBegin() 
	{
		if (m_rigidBody != nullptr) 
		{
			// Register rigid body with physics context
			m_self = GetParent()->GetComponentOfType<RigidBody>();
			GetCore()->GetPhysicsContext()->RegisterRigidBody(m_self.lock());

			// Set origin
			glm::vec3 pos = GetParent()->GetTransform()->GetPosition();
			m_rigidBody->getWorldTransform().setOrigin(btVector3(pos.x, pos.y, pos.z));
		}
		else 
		{
			// Attempt to create bullet rigid body and register it with the physics context
		}

		m_removed = false;
	}

	RigidBody::RigidBody(shared<Collider> _collider, btScalar _mass) :
		m_collider(_collider),
		m_posLock(1.0f,1.0f,1.0f)
	{
		btVector3 localInertia(0, 0, 0);

		// If mass isn't zero, rigidbody is dynamic
		if (_mass != 0.f) 
		{
			_collider->m_collisionShape->calculateLocalInertia(_mass, localInertia);
		}

		btMotionState* motionState = new btDefaultMotionState(*(_collider->m_transform));
		btRigidBody::btRigidBodyConstructionInfo rbInfo(_mass, motionState, _collider->m_collisionShape.get(), localInertia);
		m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
	}

	void RigidBody::OnRemove() 
	{
		/// If this is being removed before engine stop
		GetCore()->GetPhysicsContext()->UnregisterRigidBody(m_self.lock());
		m_removed = true;
	}

	bool RigidBody::NeedsUniqueness() const
	{
		return true;
	}

	RigidBody::~RigidBody() 
	{
		// If this is being removed before engine stop
		if (!m_removed && GetCore() != nullptr)
		{
			GetCore()->GetPhysicsContext()->UnregisterRigidBody(m_self.lock());
		}
	}

	void RigidBody::ApplyImpulse(const glm::vec3& _impulse, const glm::vec3& _relativePos) 
	{
		m_rigidBody->applyImpulse(btVector3(_impulse.x, _impulse.y, _impulse.z), btVector3(_relativePos.x, _relativePos.y, _relativePos.z));
		// Activate the rigidbody to make sure it isn't sleeping
		Activate();
	}
	void RigidBody::ApplyTorque(const glm::vec3& _torque) 
	{
		m_rigidBody->applyTorque(btVector3(_torque.x, _torque.y, _torque.z));
		// Activate the rigidbody to make sure it isn't sleeping
		Activate();
	}

	void RigidBody::Activate() 
	{
		m_rigidBody->activate();
	}
}