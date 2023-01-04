#include "PhysicsContext.h"
#include "components/RigidBody.h"
#include "Entity.h"
#include "Core.h"

namespace eengine
{
	PhysicsContext::PhysicsContext() :
		m_fixedTimeStep(1.0f/60.0f),
		m_maxSubSteps(0)
	{
		m_collisionConfig = std::make_shared<btDefaultCollisionConfiguration>();
		m_collisionDispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfig.get());

		//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		m_broadphaseInterface = std::make_shared<btDbvtBroadphase>();

		m_impulseSolver = std::make_shared<btSequentialImpulseConstraintSolver>();

		m_dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(m_collisionDispatcher.get(), m_broadphaseInterface.get(), m_impulseSolver.get(), m_collisionConfig.get());
		m_dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
	}

	void PhysicsContext::RegisterRigidBody(shared<RigidBody> _rb) 
	{
		m_rigidBodies.push_back(_rb);
		m_dynamicsWorld->addRigidBody(_rb->m_rigidBody.get());
	}

	void PhysicsContext::UnregisterRigidBody(shared<RigidBody> _rb) 
	{
		m_dynamicsWorld->removeRigidBody(_rb->m_rigidBody.get());
		delete _rb->m_rigidBody->getMotionState();
		m_rigidBodies.remove(_rb);
	}

	void PhysicsContext::Update(float _variableTimeStep) 
	{
		m_dynamicsWorld->stepSimulation(_variableTimeStep, 0, m_fixedTimeStep);
		UpdateTransforms();
	}

	void PhysicsContext::UpdateFixed(float _variableTimeStep) 
	{
		m_dynamicsWorld->stepSimulation(_variableTimeStep, m_maxSubSteps, m_fixedTimeStep);
		UpdateTransforms();
	}

	void PhysicsContext::UpdateTransforms() 
	{
		for (shared<RigidBody> rb : m_rigidBodies) 
		{
			auto eTransform = rb->GetParent()->GetTransform();
			auto bTransform = rb->m_rigidBody->getWorldTransform();

			// Enforce user-made changes
			if (eTransform->m_rotDirty || eTransform->m_posDirty) 
			{
				// Activate the rigidbody to make sure it isn't sleeping
				rb->Activate();

				if (eTransform->m_posDirty) 
				{
					auto pos = eTransform->GetPosition();
					bTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
				}
				
				if (eTransform->m_rotDirty) 
				{
					auto rot = eTransform->GetQuaternionRotation();
					bTransform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
				}
			
				rb->m_rigidBody->setWorldTransform(bTransform);
				eTransform->m_rotDirty = eTransform->m_posDirty = false;
				continue;
			}

			// Position
			btVector3 newPos = bTransform.getOrigin();
			eTransform->SetPosition(newPos.x(), newPos.y(), newPos.z());
			eTransform->m_posDirty = false; // This should only be true with other uses of SetPosition!

			// Rotation
			btQuaternion newRot = bTransform.getRotation();
			eTransform->SetRotation(glm::quat(newRot.w(), newRot.x(), newRot.y(), newRot.z()));
			eTransform->m_rotDirty = false; // This should only be true with other uses of SetRotation!
		}
	}

	PhysicsContext::~PhysicsContext() 
	{
		//remove the rigidbodies from the dynamics world
		for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			m_dynamicsWorld->removeCollisionObject(m_dynamicsWorld->getCollisionObjectArray()[i]);
		}
	}
}