#include "PhysicsContext.h"

namespace eengine
{
	PhysicsContext::PhysicsContext()
	{
		m_collisionConfig = std::make_shared<btDefaultCollisionConfiguration>();
		m_collisionDispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfig.get());

		//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		m_broadphaseInterface = std::make_shared<btDbvtBroadphase>();

		m_impulseSolver = std::make_shared<btSequentialImpulseConstraintSolver>();

		m_dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(m_collisionDispatcher.get(), m_broadphaseInterface.get(), m_impulseSolver.get(), m_collisionConfig.get());
		m_dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
	}

	PhysicsContext::~PhysicsContext() 
	{
	}
}