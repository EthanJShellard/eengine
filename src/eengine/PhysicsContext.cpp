#include "PhysicsContext.h"
#include "components/RigidBody.h"
#include "Entity.h"
#include "Core.h"
#include "Debug.h"

#include <tuple>
#include <unordered_map>

namespace eengine
{
	

	struct CollisionStatus 
	{
		CollisionStatus(shared<RigidBody> _rb1, shared<RigidBody> _rb2, bool _colliding) :
			rb1(_rb1),
			rb2(_rb2),
			stillColliding(_colliding)
		{
		}

		shared<RigidBody> rb1;
		shared<RigidBody> rb2;
		bool stillColliding;
	};

	/// Keep track of currently active collisions. Need globalness to interact with NearCallback(), which cannot be a member funtion.
	std::vector<std::tuple<shared<RigidBody>, shared<RigidBody>, btDispatcherInfo>> g_newCollisions;
	std::unordered_map< uint64_t, CollisionStatus > g_collisionMap;
	bool g_collisionsUpdated = false;

	void NearCallback(btBroadphasePair& _collisionPair, btCollisionDispatcher& _dispatcher, const btDispatcherInfo& _dispatchInfo)
	{
		// Get RigidBodies
		btRigidBody* rigidBody1 = (btRigidBody*)(_collisionPair.m_pProxy0->m_clientObject);
		btRigidBody* rigidBody2 = (btRigidBody*)(_collisionPair.m_pProxy1->m_clientObject);
		
		uint32_t idx1 = rigidBody1->getUserIndex();
		uint32_t idx2 = rigidBody2->getUserIndex();

		// Make sure we're always combining in the same order
		bool firstGreater = idx1 > idx2;
		shared<RigidBody> rb1 = firstGreater ? rigidBody1->m_eengineParent.lock() : rigidBody2->m_eengineParent.lock();
		shared<RigidBody> rb2 = firstGreater ? rigidBody2->m_eengineParent.lock() : rigidBody1->m_eengineParent.lock();

		// Create combo of IDs
		uint64_t comboID = firstGreater ? idx1 << 32 : idx2 << 32;
		comboID |= comboID ? idx2 : idx1;

		// Record collisions
		auto itr = g_collisionMap.find(comboID);
		if (itr == g_collisionMap.end())
		{
			g_collisionMap.insert({ comboID, CollisionStatus(rb1, rb2, true)});
			g_newCollisions.push_back({ rb1, rb2, _dispatchInfo });
		}
		else 
		{
			itr->second.stillColliding = true;
		}

		g_collisionsUpdated = true;

		_dispatcher.defaultNearCallback(_collisionPair, _dispatcher, _dispatchInfo);
	}

	PhysicsContext::PhysicsContext() :
		m_fixedTimeStep(1.0f/60.0f),
		m_maxSubSteps(5),
		m_rigidBodyCount(0)
	{
		m_collisionConfig = std::make_shared<btDefaultCollisionConfiguration>();
		m_collisionDispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfig.get());

		m_collisionDispatcher->setNearCallback(NearCallback);

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
		_rb->m_rigidBody->m_eengineParent = _rb;
		_rb->m_rigidBody->setUserIndex(m_rigidBodyCount++);
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
		SendCollisionEvents();
	}

	void PhysicsContext::UpdateFixed(float _variableTimeStep) 
	{
		m_dynamicsWorld->stepSimulation(_variableTimeStep, m_maxSubSteps, m_fixedTimeStep);
		UpdateTransforms();
		SendCollisionEvents();
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
				else 
				{
					btVector3 newPos = bTransform.getOrigin();
					eTransform->SetPosition(newPos.x(), newPos.y(), newPos.z());
				}
				
				if (eTransform->m_rotDirty) 
				{
					auto rot = eTransform->GetQuaternionRotation();
					bTransform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
				}
				else 
				{
					btQuaternion newRot = bTransform.getRotation();
					eTransform->SetRotation(glm::quat(newRot.w(), newRot.x(), newRot.y(), newRot.z()));
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

	void PhysicsContext::SendCollisionEvents() 
	{
		// Only do these if we've updated collisions.
		if (!g_collisionsUpdated) 
		{
			return;
		}

		for (auto c : g_newCollisions) 
		{
			shared<RigidBody> rb1, rb2;
			btDispatcherInfo info;
			std::tie(rb1, rb2, info) = c;

			// OnTriggerEnter events
			if (rb1->m_isTrigger ) 
			{
				if (rb2->m_isTrigger) 
				{
					// Not going to send OnTriggerEnter events when triggers enter triggers
					return;
				}

				rb1->GetParent()->OnTriggerEnter(rb2);
			}

			if (rb2->m_isTrigger) 
			{
				rb2->GetParent()->OnTriggerEnter(rb1);
			}
		}

		// Check for collision exits
		auto itr = g_collisionMap.begin();
		while (itr != g_collisionMap.end()) 
		{
			if (!itr->second.stillColliding) 
			{
				// Send exiting events
				if (itr->second.rb1->m_isTrigger && !itr->second.rb2->m_isTrigger) 
				{
					itr->second.rb1->GetParent()->OnTriggerExit(itr->second.rb2);
				}
				if (itr->second.rb2->m_isTrigger && !itr->second.rb1->m_isTrigger)
				{
					itr->second.rb2->GetParent()->OnTriggerExit(itr->second.rb1);
				}
				itr = g_collisionMap.erase(itr);
			}
			else 
			{
				// Still colliding, continue
				itr->second.stillColliding = false;
				itr++;
			}
		} // Collision map loop

		g_newCollisions.clear();
		g_collisionsUpdated = false;
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