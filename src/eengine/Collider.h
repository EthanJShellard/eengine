#include "eengine_defines.h"

#include <pellet/btBulletCollisionCommon.h>

namespace eengine
{
	// Engine forward declarations
	class RigidBody;

	class Collider 
	{
		friend class RigidBody;

		// Create a system for sharing these, maybe using resources...
		shared<btCollisionShape> m_collisionShape;
		shared<btTransform> m_transform;

	public:
		void SetSphere();
		void SetCube();
		void SetCapsule();
		void SetCone();
		void SetCylinder();
	};
}