#ifndef EENGINE_TRANSFORM
#define EENGINE_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Component.h"

namespace eengine 
{
	/// @brief Class which handles position, rotation and scale.
	class Transform : public Component
	{
		friend class PhysicsContext;
		friend class RigidBody;

	private:
		glm::vec3 m_position;
		glm::quat m_orientation;
		glm::vec3 m_scale;
		glm::mat4 m_modelMatrix;
		glm::mat4 m_scaleMatrix;
		glm::mat4 m_rotationMatrix;
		glm::mat4 m_translationMatrix;

		bool m_dirty;
		bool m_posDirty; // Use only to inform physics context of updates to position
		bool m_rotDirty; // Use only to inform physics context of updates to position
	public:
		Transform();

		/// @brief Set the position of this Transform.
		/// @param _newPos The new position of this Transform.
		void SetPosition(glm::vec3 _newPos);

		/// @brief Set the position of this transform.
		/// @param _x The new x axis position.
		/// @param _y The new y axis position.
		/// @param _z The new z axis position.
		void SetPosition(float _x, float _y, float _z);

		/// @brief Set the rotation/orientation of this Transform.
		/// @param _newRot The new rotation in Euler angles.
		void SetRotation(glm::vec3 _newRot);

		/// @brief Set the rotation/orientation of this Transform with Euler angles.
		/// @param _x The new x axis rotation.
		/// @param _y The new y axis rotation.
		/// @param _z The new z axis rotation.
		void SetRotation(float _x, float _y, float _z);

		/// @brief Set the rotation/orientation of this Transform with a quaternion.
		/// @param _newRot The new quaternion orientation.
		void SetRotation(glm::quat _newRot);

		/// @brief Set the scale of this Transform.
		/// @param _newScale The new scale.
		void SetScale(glm::vec3 _newScale);

		/// @brief Set the scale of this Transform.
		/// @param _x The new x axis scale.
		/// @param _y The new y axis scale.
		/// @param _z The new z axis scale.
		void SetScale(float _x, float _y, float _z);

		/// @brief Get the current position of this Transform.
		/// @return The current position.
		glm::vec3 GetPosition() const;

		/// @brief Get the current rotation/orientation of this Transform as Euler angles.
		/// @return The current rotation/orientation as Euler angles.
		glm::vec3 GetRotation() const;

		/// @brief Get the current rotation/orientation of this Transform as a quaternion.
		/// @return The current rotation/orientation as a quaternion.
		glm::quat GetQuaternionRotation() const;

		/// @brief Get the current scale of this Transform.
		/// @return The current scale.
		glm::vec3 GetScale() const;

		/// @brief Get a vector pointing right from this Transform's perspective.
		/// @return Right with respect to this Transform.
		glm::vec3 Right() const;

		/// @brief Get a vector pointing up from this Transform's perspective.
		/// @return Up with respect to this Transform.
		glm::vec3 Up() const;

		/// @brief Get a vector pointing forward from this Transform's perspective.
		/// @return Forward with respect to this Transform.
		glm::vec3 Forward() const;

		/// @brief Rotate this Transform.
		/// @param _angle Angle in degrees by which this Transform will be rotated.
		/// @param _axis Axis around which this rotation will take place.
		void Rotate(float _angle, glm::vec3 _axis);

		/// @brief Translate this Transform.
		/// @param _move How far the Transform will translate in each axis.
		void Translate(glm::vec3 _move);

		/// @brief Scale this Transform.
		/// @param _scaleFactors Factors by which this Transform's scale will be multiplied along the corresponding axes.
		void Scale(glm::vec3 _scaleFactors);

		/// @brief Get a model matrix representing the combined transformations affecting this Transform.
		/// @details This matrix will be computed and cached only once for each time the Transform's internal state is dirtied.
		/// @return A matrix representing this Transform's scale, orientation and position.
		glm::mat4 GetModelMatrix();
	};
}
#endif // EENGINE_TRANSFORM