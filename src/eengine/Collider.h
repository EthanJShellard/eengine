#ifndef EENGINE_COLLIDER
#define EENGINE_COLLIDER

#include "eengine_defines.h"
#include "NonCopyable.h"

#include <pellet/btBulletCollisionCommon.h>

namespace eengine
{
	// Engine forward declarations
	class RigidBody;

	class Collider : public NonCopyable 
	{
		friend class RigidBody;

	protected:
		// Create a system for sharing these, maybe using resources...
		shared<btCollisionShape> m_collisionShape;
		shared<btTransform> m_transform;

		Collider();
	};
}

#endif // EENGINE_COLLIDER