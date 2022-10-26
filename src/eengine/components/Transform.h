#ifndef EENGINE_TRANSFORM
#define EENGINE_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Component.h"

namespace eengine 
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_position;
		glm::quat m_orientation;
		glm::vec3 m_scale;
		glm::mat4 m_modelMatrix;
		glm::mat4 m_scaleMatrix;
		glm::mat4 m_rotationMatrix;
		glm::mat4 m_translationMatrix;

		bool m_dirty;
	public:
		Transform();

		void SetPosition(glm::vec3 _newPos);
		void SetPosition(float _x, float _y, float _z);
		void SetRotation(glm::vec3 _newRot);
		void SetRotation(float _x, float _y, float _z);
		void SetRotation(glm::quat _newRot);
		void SetScale(glm::vec3 _newScale);
		void SetScale(float _x, float _y, float _z);

		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::quat GetQuaternionRotation();
		glm::vec3 GetScale();
		glm::vec3 Right();
		glm::vec3 Up();
		glm::vec3 Forward();

		void Rotate(float _angle, glm::vec3 _axis);
		void Translate(glm::vec3 _move);
		void Scale(glm::vec3 _scaleFactors);

		glm::mat4 GetModelMatrix();
	};
}
#endif // EENGINE_TRANSFORM