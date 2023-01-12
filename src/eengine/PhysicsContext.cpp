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

		weak<RigidBody> rb1;
		weak<RigidBody> rb2;
		bool stillColliding;
	};

	struct CollisionInfo 
	{
		
		CollisionInfo(shared<RigidBody> _rb1, shared<RigidBody> _rb2, btDispatcherInfo _info) : 
			rb1(_rb1),
			rb2(_rb2),
			info(_info)
		{
		}

		weak<RigidBody> rb1;
		weak<RigidBody> rb2;
		btDispatcherInfo info;
	};

	/// Keep track of currently active collisions. Need globalness to interact with NearCallback(), which cannot be a member function.
	std::vector<CollisionInfo> g_newCollisions;
	std::unordered_map< uint64_t, CollisionStatus > g_collisionMap;

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
		uint64_t comboID = firstGreater ? (uint64_t)idx1 << 32 : (uint64_t)idx2 << 32;
		comboID |= firstGreater ? (uint64_t)idx2 : (uint64_t)idx1;

		// Record collisions
		auto itr = g_collisionMap.find(comboID);
		if (itr == g_collisionMap.end())
		{
			g_collisionMap.insert({ comboID, CollisionStatus(rb1, rb2, true)});
			g_newCollisions.push_back(CollisionInfo(rb1, rb2, _dispatchInfo));
		}
		else 
		{
			itr->second.stillColliding = true;
		}

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

		// MSalters, https://stackoverflow.com/questions/10120623/removing-item-from-list-of-weak-ptrs
		m_rigidBodies.remove_if([_rb](std::weak_ptr<RigidBody> p) { return !(p.owner_before(_rb) || _rb.owner_before(p)); });
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
		// It is possible to avoid some of this by using MotionState inheritance instead

		for (weak<RigidBody> weak_rb : m_rigidBodies) 
		{
			auto rb = weak_rb.lock();
			auto eTransform = rb->GetParent()->GetTransform();
			btTransform bTransform;
			rb->m_rigidBody->getMotionState()->getWorldTransform(bTransform);

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

			if (rb->GetIsStatic() || rb->GetIsKinematic()) 
			{
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
		if (!m_dynamicsWorld->m_steppedInternalSimulation) 
		{
			return;
		}
		
		// Reset flag
		m_dynamicsWorld->m_steppedInternalSimulation = false;

		for (CollisionInfo c : g_newCollisions) 
		{
			auto rb1 = c.rb1.lock();
			auto rb2 = c.rb2.lock();

			// Either rb1 or rb2 no longer exists, skip this collision.
			if (!rb1 || !rb2) 
			{
				continue;
			}

			if (rb1->m_isTrigger) 
			{
				rb1->GetParent()->OnTriggerEnter(rb2);
			}
			else 
			{
				rb1->GetParent()->OnCollisionEnter(rb2);
			}

			if (rb2->m_isTrigger)
			{
				rb2->GetParent()->OnTriggerEnter(rb1);
			}
			else
			{
				rb2->GetParent()->OnCollisionEnter(rb1);
			}
		}

		// Check for collision exits
		auto itr = g_collisionMap.begin();
		while (itr != g_collisionMap.end()) 
		{
			if (!itr->second.stillColliding) 
			{
				CollisionStatus cs = itr->second;
				auto rb1 = cs.rb1.lock();
				auto rb2 = cs.rb2.lock();

				// Either rb1 or rb2 no longer exists, skip this collision.
				if (!rb1 || !rb2)
				{
					itr++;
					continue;
				}

				// Send exiting events
				if (rb1->m_isTrigger)
				{
					rb1->GetParent()->OnTriggerExit(rb2);
				}
				else
				{
					rb1->GetParent()->OnCollisionExit(rb2);
				}

				if (rb2->m_isTrigger)
				{
					rb2->GetParent()->OnTriggerExit(rb1);
				}
				else
				{
					rb2->GetParent()->OnCollisionExit(rb1);
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
	}

	RayCastResult PhysicsContext::RayCast(const glm::vec3& _origin, const glm::vec3& direction, float distance) const
	{
		// A good next step would be to add collision masking.

		btVector3 from(_origin.x, _origin.y, _origin.z);
		glm::vec3 glmTo = _origin + (distance * glm::normalize(direction));
		btVector3 to(glmTo.x, glmTo.y, glmTo.z);

		btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);

		m_dynamicsWorld->rayTest(from, to, rayCallback);

		RayCastResult result;

		if (rayCallback.hasHit()) 
		{
			result.didHit = true;

			const btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);
			result.hitRigidBody = body->m_eengineParent;
			result.distanceFraction = rayCallback.m_closestHitFraction;
			result.hitPointInWorld = glm::vec3(rayCallback.m_hitPointWorld.x(), rayCallback.m_hitPointWorld.y(), rayCallback.m_hitPointWorld.z());
			result.hitPointNormal = glm::vec3(rayCallback.m_hitNormalWorld.x(), rayCallback.m_hitNormalWorld.y(), rayCallback.m_hitNormalWorld.z());
		}
		else 
		{
			result.didHit = false;
		}

		return result;
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