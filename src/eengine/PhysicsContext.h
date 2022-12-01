#include "eengine_defines.h"
#include "NonCopyable.h"

#include <pellet/btBulletDynamicsCommon.h>

#include <list>

namespace eengine 
{
	class RigidBody;

	class PhysicsContext : public NonCopyable
	{
		friend class Core;
		friend class RigidBody;

		shared<btDiscreteDynamicsWorld> m_dynamicsWorld;
		shared<btCollisionConfiguration> m_collisionConfig;
		shared<btCollisionDispatcher> m_collisionDispatcher;
		shared<btBroadphaseInterface> m_broadphaseInterface;
		shared<btSequentialImpulseConstraintSolver> m_impulseSolver;

		std::list<shared<RigidBody>> m_rigidBodies;

		float m_fixedTimeStep;
		// Use to interpolate between fixed timesteps
		int m_maxSubSteps;

		PhysicsContext();

		void RegisterRigidBody(shared<RigidBody> _rb);
		void UnregisterRigidBody(shared<RigidBody> _rb);

		void Update(float _variableTimeStep);
		void UpdateFixed(float _variableTimeStep);

		void UpdateTransforms();
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

		~PhysicsContext();
	};
}