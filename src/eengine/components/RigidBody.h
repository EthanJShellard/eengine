#include "../Component.h"
#include "../eengine_defines.h"

#include <pellet/btBulletDynamicsCommon.h>

namespace eengine 
{
	// Engine forward declarations
	class Collider;

	class RigidBody : public Component 
	{
		friend class PhysicsContext;

		shared<Collider> m_collider;
		shared<btRigidBody> m_rigidBody;
		weak<RigidBody> m_self;
		bool m_removed;
		btVector3 m_posLock;
		btVector3 m_rotLock;

		void OnBegin();
		void OnRemove();

		void Activate();
	public:

		/// @brief Create a RigidBody with a collider and set mass.
		/// @param _collider The new RigidBody's collider.
		/// @param _mass The new RigidBody's mass.
		RigidBody(shared<Collider> _collider, float _mass);

		~RigidBody();

		bool NeedsUniqueness() const;

		/// @brief Set whether the x axis position of this RigidBody should be locked.
		/// @param _lock Should the x axis position be locked.
		void SetXPosLocked(bool _lock) { m_posLock.setX(!_lock); m_rigidBody->setLinearFactor(m_posLock); }
		/// @brief Set whether the y axis position of this RigidBody should be locked.
		/// @param _lock Should the y axis position be locked.
		void SetYPosLocked(bool _lock) { m_posLock.setY(!_lock); m_rigidBody->setLinearFactor(m_posLock); }
		/// @brief Set whether the z axis position of this RigidBody should be locked.
		/// @param _lock Should the z axis position be locked.
		void SetZPosLocked(bool _lock) { m_posLock.setZ(!_lock); m_rigidBody->setLinearFactor(m_posLock); }

		/// @brief Set whether the x axis rotation of this RigidBody should be locked.
		/// @param _lock Should the x axis rotation be locked.
		void SetXRotLocked(bool _lock) { m_rotLock.setX(!_lock); m_rigidBody->setAngularFactor(m_posLock); }
		/// @brief Set whether the y axis rotation of this RigidBody should be locked.
		/// @param _lock Should the y axis rotation be locked.
		void SetYRotLocked(bool _lock) { m_rotLock.setY(!_lock); m_rigidBody->setAngularFactor(m_posLock); }
		/// @brief Set whether the z axis rotation of this RigidBody should be locked.
		/// @param _lock Should the z axis rotation be locked.
		void SetZRotLocked(bool _lock) { m_rotLock.setZ(!_lock); m_rigidBody->setAngularFactor(m_posLock); }

		/// @brief Apply an immediate impulse to this RigidBody.
		/// @param _impulse The impulse vector.
		/// @param _relativePos The impulse's location relative to this RigidBody.
		void ApplyImpulse(const glm::vec3& _impulse, const glm::vec3& _relativePos);

		/// @brief Apply an immediate torque to this RigidBody.
		/// @param _torque The torque to be applied in each axis.
		void ApplyTorque(const glm::vec3& _torque);
	};
}