#include "../Component.h"
#include "../eengine_defines.h"

#include <pellet/btBulletDynamicsCommon.h>

namespace eengine 
{
	// Engine forward declarations
	class Collider;

	class RigidBody : public Component 
	{
		shared<Collider> m_collider;
		shared<btDefaultMotionState> m_motionState;
		shared<btRigidBody> m_rigidBody;

		void OnBegin();

	public:
		RigidBody(shared<Collider> _collider, float _mass);
	};
}