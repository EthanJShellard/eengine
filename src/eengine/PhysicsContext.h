#include "eengine_defines.h"
#include "NonCopyable.h"

#include <pellet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <list>

namespace eengine 
{
	class RigidBody;

	struct RayCastResult 
	{
		bool didHit = false;

		glm::vec3 hitPointInWorld = glm::vec3(0);
		glm::vec3 hitPointNormal = glm::vec3(0);
		float distanceFraction = 1.0f;

		weak<RigidBody> hitRigidBody;
	};

	class PhysicsContext : public NonCopyable
	{
		friend class Core;
		friend class RigidBody;

		shared<btDiscreteDynamicsWorld> m_dynamicsWorld;
		shared<btCollisionConfiguration> m_collisionConfig;
		shared<btCollisionDispatcher> m_collisionDispatcher;
		shared<btBroadphaseInterface> m_broadphaseInterface;
		shared<btSequentialImpulseConstraintSolver> m_impulseSolver;

		std::list<weak<RigidBody>> m_rigidBodies;

		float m_fixedTimeStep;
		// Use to interpolate between fixed timesteps
		int m_maxSubSteps;
		// Used for generating IDs
		uint32_t m_rigidBodyCount;

		PhysicsContext();

		void RegisterRigidBody(shared<RigidBody> _rb);
		void UnregisterRigidBody(shared<RigidBody> _rb);

		void Update(float _variableTimeStep);
		void UpdateFixed(float _variableTimeStep);

		void UpdateTransforms();
		void SendCollisionEvents();
	public:
		
		/// @brief Set the engine physics' fixed timestep.
		/// @param _newFixedTimeStep The new fixed timestep.
		void SetFixedTimeStep(float _newFixedTimeStep) { m_fixedTimeStep = _newFixedTimeStep; }

		/// @brief Get the engine physics' fixed timestep.
		/// @return The current fixed timestep.
		float GetFixedTimeStep() const { return m_fixedTimeStep; }

		/// @brief Set the engine physics' maximum number of substeps per physics iteration. This will determine how fine-grain interpolation is.
		/// @param _newMaxSubsteps The new maximum substep count.
		void SetMaxSubSteps(int _newMaxSubsteps) { m_maxSubSteps = _newMaxSubsteps; }

		/// @brief Get the engine physics' maximum number of substeps per physics iteration.
		/// @return The current maximum substep count.
		int GetMaxSubsteps() const { return m_maxSubSteps; }

		/// @brief Casts a ray through the physics world, returning information about potential collsions.
		/// @param _origin Where the ray will start.
		/// @param _direction The direction the ray will travel in.
		/// @param _distance The distance the ray will travel without collision before stopping.
		/// @return A RayCastResult struct, containing information about the cast.
		RayCastResult RayCast(const glm::vec3& _origin, const glm::vec3& _direction, float _distance) const;

		~PhysicsContext();
	};
}