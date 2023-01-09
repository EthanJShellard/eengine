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
		m_posLock(1.0f, 1.0f, 1.0f),
		m_isTrigger(false)
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

	void RigidBody::ApplyCentralForce(const glm::vec3& _force) 
	{
		m_rigidBody->applyCentralForce(btVector3(_force.x, _force.y, _force.z));
		// Activate the rigidbody to make sure it isn't sleeping
		Activate();
	}

	void RigidBody::SetVelocity(const glm::vec3& _velocity) 
	{
		m_rigidBody->setLinearVelocity(btVector3(_velocity.x, _velocity.y, _velocity.z));
		// Activate the rigidbody to make sure it isn't sleeping
		Activate();
	}

	glm::vec3 RigidBody::GetVelocity() const 
	{
		auto vel = m_rigidBody->getLinearVelocity();
		return glm::vec3(vel.x(), vel.y(), vel.z());
	}

	void RigidBody::SetFriction(float _friction) 
	{
		m_rigidBody->setFriction(_friction);
	}

	float RigidBody::GetFriction() const
	{
		return m_rigidBody->getFriction();
	}

	void RigidBody::Activate() 
	{
		m_rigidBody->activate();
	}

	void RigidBody::SetIsTrigger(bool _isTrigger) 
	{
		if (_isTrigger != (m_rigidBody->getCollisionFlags() & btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE)) 
		{
			m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() ^ btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE);
		}
		
		m_isTrigger = _isTrigger;
	}

	bool RigidBody::GetIsTrigger() const
	{
		return m_isTrigger;
	}

	void RigidBody::SetIsKinematic(bool _isKinematic) 
	{
		if (_isKinematic != (m_rigidBody->getCollisionFlags() & btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT)) 
		{
			m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() ^ btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT);
		}

		// Force initial transform update
		auto transform = GetParent()->GetTransform();
		transform->m_posDirty = true;
		transform->m_rotDirty = true;
	}

	bool RigidBody::GetIsKinematic() const
	{
		return m_rigidBody->isKinematicObject();
	}
}