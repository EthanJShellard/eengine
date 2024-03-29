#include "../Component.h"
#include "../eengine_defines.h"

#include <pellet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

namespace eengine 
{
	// Engine forward declarations
	class Collider;

	/// @brief Component representing a physics rigid body. Currently supports only single colliders.
	class RigidBody : public Component 
	{
		friend class PhysicsContext;

		shared<Collider> m_collider;
		shared<btRigidBody> m_rigidBody;
		
		weak<RigidBody> m_self;
		bool m_removed;
		bool m_registered;
		bool m_isTrigger;
		btVector3 m_posLock;
		btVector3 m_rotLock;
		glm::vec3 m_gravity;
		bool m_gravityOverride;
		btScalar m_mass;
		bool m_disabled;

		void OnBegin() override;
		void OnRemove() override;
		void OnDelete() override;
		void OnDisable() override;
		void OnEnable() override;

		void Activate();

		void TempRemoveBegin();
		void TempRemoveEnd();
	public:
		/// @brief Create a RigidBody with a collider and set mass.
		/// @param _collider The new RigidBody's collider.
		/// @param _mass The new RigidBody's mass.
		RigidBody(shared<Collider> _collider, float _mass);

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
		/// @brief Set which axes this RigidBody should have its position locked in.
		/// @param _lockX Lock the X axis?
		/// @param _lockY Lock the Y axis?
		/// @param _lockZ Lock the Z axis?
		void SetPositionAxesLocked(bool _lockX, bool _lockY, bool _lockZ) { m_posLock.setValue(!_lockX, !_lockY, !_lockZ); m_rigidBody->setLinearFactor(m_posLock); }

		/// @brief Set whether the x axis rotation of this RigidBody should be locked.
		/// @param _lock Should the x axis rotation be locked.
		void SetXRotLocked(bool _lock) { m_rotLock.setX(!_lock); m_rigidBody->setAngularFactor(m_posLock); }
		/// @brief Set whether the y axis rotation of this RigidBody should be locked.
		/// @param _lock Should the y axis rotation be locked.
		void SetYRotLocked(bool _lock) { m_rotLock.setY(!_lock); m_rigidBody->setAngularFactor(m_posLock); }
		/// @brief Set whether the z axis rotation of this RigidBody should be locked.
		/// @param _lock Should the z axis rotation be locked.
		void SetZRotLocked(bool _lock) { m_rotLock.setZ(!_lock); m_rigidBody->setAngularFactor(m_posLock); }
		/// @brief Set which axes this RigidBody should have its rotation locked in.
		/// @param _lockX Lock the X axis?
		/// @param _lockY Lock the Y axis?
		/// @param _lockZ Lock the Z axis?
		void SetRotationAxesLocked(bool _lockX, bool _lockY, bool _lockZ) { m_rotLock.setValue(!_lockX, !_lockY, !_lockZ); m_rigidBody->setAngularFactor(m_rotLock); }

		/// @brief Apply an immediate impulse to this RigidBody.
		/// @param _impulse The impulse vector.
		/// @param _relativePos The impulse's location relative to this RigidBody.
		void ApplyImpulse(const glm::vec3& _impulse, const glm::vec3& _relativePos);

		/// @brief Apply an immediate torque to this RigidBody.
		/// @param _torque The torque to be applied in each axis.
		void ApplyTorque(const glm::vec3& _torque);

		/// @brief Apply a central force to this RigidBody.
		/// @param _force The force to be applied.
		void ApplyCentralForce(const glm::vec3& _force);

		/// @brief Set the linear velocity of this RigidBody.
		/// @param _velocity The new linear velocity of this RigidBody.
		void SetVelocity(const glm::vec3& _velocity);

		/// @brief Get the linear velocity of this RigidBody.
		/// @return The linear velocity of this RigidBody.
		glm::vec3 GetVelocity() const;

		/// @brief Set the friction ratio of this RigidBody.
		/// @param friction The new friction ratio.
		void SetFriction(float _friction);

		/// @brief Get the friction ratio of this RigidBody.
		/// @return The friction ratio of this RigidBody.
		float GetFriction() const;

		/// @brief Set a gravity override for this RigidBody.
		/// @param _gravity The gravity override.
		void SetGravity(const glm::vec3& _gravity);

		/// @brief Get the current gravitational acceleration of this object.
		/// @return The gravitational acceleration. 
		glm::vec3 GetGravity() const;

		/// @brief Set scale factors for this RigidBody's collider's dimensions.
		/// @param _newScale The scale factors.
		void SetColliderScale(const glm::vec3& _newScale);

		/// @brief Get the scale factors for this RigidBody's collider's dimensions.
		/// @return The scale factors.
		glm::vec3 GetColliderScale() const;

		/// @brief Set whether or not this RigidBody's collider will act as a trigger.
		/// @param _isTrigger Whether or not this RigidBody's collider will act as a trigger.
		void SetIsTrigger(bool _isTrigger);

		/// @brief Get whether or not this RigidBody's collider is set to act as a trigger.
		/// @return Whether or not this RigidBody's collider is set to act as a trigger.
		bool GetIsTrigger() const;

		/// @brief Set whether or not this RigidBody should be kinematic.
		/// @param _isKinematic Whether or not this RigidBody should be kinematic.
		/// @details Kinematic RigidBodies are not affected by forced or collisions.
		void SetIsKinematic(bool _isKinematic);

		/// @brief Get whether or not this RigidBody is kinematic.
		/// @return Whether or not this RigidBody is kinematic.
		/// @details Kinematic RigidBodies are not affected by forced or collisions.
		bool GetIsKinematic() const;

		/// @brief Set whether or not this RigidBody should be Static.
		/// @param _isStatic Whether or not this RigidBody should be static.
		/// @details Static RigidBodies are not affected by forces or collisions and do not move.
		void SetIsStatic(bool _isStatic);

		/// @brief Set whether or not this RigidBody should be Static.
		/// @return Whether or not this RigidBody should be Static.
		/// @details Static RigidBodies are not affected by forces or collisions and do not move.
		bool GetIsStatic() const;

		/// @brief Set whether or not this RigidBody is enabled.
		/// @param _isEnabled Whether or not this RigidBody should be enabled.
		/// @details Disabled RigidBodies are removed from the physics environment until they are reenabled.
		void SetIsEnabled(bool _isEnabled);

		/// @brief Get whether or not this RigidBody is enabled.
		/// @return Whether or not this RigidBody is enabled.
		/// @details Disabled RigidBodies are removed from the physics environment until they are reenabled.
		bool GetIsEnabled() const;
	};
}