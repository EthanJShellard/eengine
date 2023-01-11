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
			m_registered = true;

			// Set origin
			glm::vec3 pos = GetParent()->GetTransform()->GetPosition();
			m_rigidBody->getWorldTransform().setOrigin(btVector3(pos.x, pos.y, pos.z));

			if (m_disabled)
			{
				TempRemoveBegin();
			}
			else 
			{
				// Set gravity if it has been overrided
				if (m_gravityOverride)
				{
					m_rigidBody->setGravity(btVector3(m_gravity.x, m_gravity.y, m_gravity.y));
				}
			}
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
		m_isTrigger(false),
		m_registered(false),
		m_mass(_mass),
		m_gravity(0.0f, 0.0f, 0.0f),
		m_gravityOverride(false),
		m_disabled(false)
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

	void RigidBody::OnDelete() 
	{
		OnRemove();
	}

	void RigidBody::OnEnable() 
	{
		SetIsEnabled(true);
	}

	void RigidBody::OnDisable() 
	{
		SetIsEnabled(false);
	}

	bool RigidBody::NeedsUniqueness() const
	{
		return true;
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
		btVector3 vel = m_rigidBody->getLinearVelocity();
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

	void RigidBody::SetGravity(const glm::vec3& _gravity)
	{
		m_rigidBody->setGravity(btVector3(_gravity.x, _gravity.y, _gravity.z));
		m_gravityOverride = true;
	}

	glm::vec3 RigidBody::GetGravity() const
	{
		if (m_gravityOverride) 
		{
			return m_gravity;
		}
		else 
		{
			auto grav = m_rigidBody->getGravity();
			return glm::vec3(grav.x(), grav.y(), grav.z());
		}
	}

	void RigidBody::SetColliderScale(const glm::vec3& _newScale) 
	{
		m_rigidBody->getCollisionShape()->setLocalScaling(btVector3(_newScale.x, _newScale.y, _newScale.z));
	}

	glm::vec3 RigidBody::GetColliderScale()
	{
		btVector3 scale = m_rigidBody->getCollisionShape()->getLocalScaling();
		return glm::vec3(scale.x(), scale.y(), scale.z());
	}

	void RigidBody::Activate() 
	{
		m_rigidBody->activate();
	}

	void RigidBody::TempRemoveBegin() 
	{
		GetCore()->GetPhysicsContext()->m_dynamicsWorld->removeRigidBody(m_rigidBody.get());
	}

	void RigidBody::TempRemoveEnd() 
	{
		GetCore()->GetPhysicsContext()->m_dynamicsWorld->addRigidBody(m_rigidBody.get());
		if (m_gravityOverride) 
		{
			m_rigidBody->setGravity(btVector3(m_gravity.x, m_gravity.y, m_gravity.y));
		}
	}

	void RigidBody::SetIsTrigger(bool _isTrigger) 
	{
		if (_isTrigger != (bool)(m_rigidBody->getCollisionFlags() & btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE)) 
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
		if (_isKinematic) 
		{
			if (m_registered) 
			{
				// Have to remove from physics world before setting mass props
				TempRemoveBegin();
				m_rigidBody->setMassProps(0.0f, m_rigidBody->getLocalInertia());
				// setMassProps will set an object as static if mass is 0 so we should remove that flag
				m_rigidBody->setCollisionFlags((m_rigidBody->getCollisionFlags() & ~btCollisionObject::CollisionFlags::CF_STATIC_OBJECT) | btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT);
				TempRemoveBegin();
			}
			else 
			{
				m_rigidBody->setMassProps(0.0f, m_rigidBody->getLocalInertia());
				// setMassProps will set an object as static if mass is 0 so we should remove that flag
				m_rigidBody->setCollisionFlags((m_rigidBody->getCollisionFlags() & ~btCollisionObject::CollisionFlags::CF_STATIC_OBJECT) | btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT);
			}
			
		}
		else 
		{
			if (m_registered) 
			{
				// Have to remove from physics world before setting mass props
				TempRemoveBegin();
				m_rigidBody->setMassProps(m_mass, m_rigidBody->getLocalInertia());
				m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() & ~btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT);
				TempRemoveEnd();
			}
			else 
			{
				m_rigidBody->setMassProps(m_mass, m_rigidBody->getLocalInertia());
				m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() & ~btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT);
			}
		}

		// Force initial transform update
		auto transform = GetParent()->GetTransform();
		transform->m_posDirty = true;
		transform->m_rotDirty = true;
	}

	void RigidBody::SetIsStatic(bool _isStatic) 
	{
		if (_isStatic) 
		{
			if (m_registered) 
			{
				// Have to remove from physics world before setting mass props
				TempRemoveBegin();
				m_rigidBody->setMassProps(0.0f, m_rigidBody->getLocalInertia());
				TempRemoveEnd();
			}
			else 
			{
				m_rigidBody->setMassProps(0.0f, m_rigidBody->getLocalInertia());
			}
		}
		else 
		{
			if (m_registered) 
			{
				// Have to remove from physics world before setting mass props
				TempRemoveBegin();
				m_rigidBody->setMassProps(m_mass, m_rigidBody->getLocalInertia());
				TempRemoveEnd();
			}
			else 
			{
				m_rigidBody->setMassProps(m_mass, m_rigidBody->getLocalInertia());
			}
		}

		// Force initial transform update
		auto transform = GetParent()->GetTransform();
		transform->m_posDirty = true;
		transform->m_rotDirty = true;
	}

	bool RigidBody::GetIsStatic() const
	{
		return m_rigidBody->isStaticObject();
	}

	bool RigidBody::GetIsKinematic() const
	{
		return m_rigidBody->isKinematicObject();
	}

	void RigidBody::SetIsEnabled(bool _isEnabled) 
	{
		if (!_isEnabled) 
		{
			m_disabled = true;
			if (m_registered)
			{
				TempRemoveBegin();
			}
		}
		else 
		{
			m_disabled = false;
			if (m_registered) 
			{
				TempRemoveEnd();
			}
		}
	}

	bool RigidBody::GetIsEnabled() const
	{
		return m_disabled;
	}
}