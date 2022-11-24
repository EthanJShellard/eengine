#include "eengine_defines.h"

#include <pellet/btBulletDynamicsCommon.h>

#include <vector>

namespace eengine 
{
	class PhysicsContext 
	{
		shared<btDiscreteDynamicsWorld> m_dynamicsWorld;
		shared<btDefaultCollisionConfiguration> m_collisionConfig;
		shared<btCollisionDispatcher> m_collisionDispatcher;
		shared<btBroadphaseInterface> m_broadphaseInterface;
		shared<btSequentialImpulseConstraintSolver> m_impulseSolver;
	public:
		PhysicsContext();
		~PhysicsContext();
	};
}