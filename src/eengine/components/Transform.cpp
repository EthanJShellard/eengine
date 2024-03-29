#include "Transform.h"

namespace eengine 
{
	Transform::Transform() :
		m_modelMatrix(glm::mat4(1.0f)),
		m_rotationMatrix(glm::mat4(1.0f)),
		m_translationMatrix(glm::mat4(1.0f)),
		m_scaleMatrix(glm::mat4(1.0f)),
		m_position(glm::vec3(0.0f)),
		m_scale(glm::vec3(1.0f)),
		m_orientation(glm::quat(glm::vec3(0.0f,0.0f,0.0f))),
		m_dirty(true),
		m_posDirty(true),
		m_rotDirty(true)
	{
	}

	void Transform::SetPosition(const glm::vec3& _newPos) 
	{
		m_position = _newPos;
		m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
		m_dirty = m_posDirty = true;
	}

	void  Transform::SetPosition(float _x, float _y, float _z)
	{
		m_position = glm::vec3(_x, _y, _z);
		m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
		m_dirty = m_posDirty = true;
	}

	void  Transform::SetRotation(const glm::vec3& _newRot)
	{
		m_orientation = glm::quat(_newRot);
		m_rotationMatrix = glm::toMat4(m_orientation);
		m_dirty = m_rotDirty = true;
	}

	void  Transform::SetRotation(float _x, float _y, float _z)
	{
		m_orientation = glm::quat(glm::vec3(_x, _y, _z));
		m_rotationMatrix = glm::toMat4(m_orientation);
		m_dirty = m_rotDirty = true;
	}

	void Transform::SetRotation(const glm::quat& _newRot)
	{
		m_orientation = _newRot;
		m_rotationMatrix = glm::toMat4(m_orientation);
		m_dirty = m_rotDirty = true;
	}

	void  Transform::SetScale(const glm::vec3& _newScale)
	{
		m_scale = _newScale;
		m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		m_dirty = true;
	}

	void  Transform::SetScale(float _x, float _y, float _z)
	{
		m_scale = glm::vec3(_x, _y, _z);
		m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		m_dirty = true;
	}

	void  Transform::Rotate(float _angle, const glm::vec3& _axis)
	{
		m_orientation = glm::angleAxis(glm::radians(_angle), _axis) * m_orientation;
		m_rotationMatrix = glm::toMat4(m_orientation);
		m_dirty = m_rotDirty = true;
	}

	void  Transform::Translate(const glm::vec3& _move)
	{
		m_position += _move;
		m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
		m_dirty = m_posDirty = true;
	}

	void Transform::Scale(const glm::vec3& _scaleFactors) 
	{
		m_scale *= _scaleFactors;
		m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		m_dirty = true;
	}

	glm::vec3  Transform::GetPosition() const
	{
		return m_position;
	}

	glm::vec3  Transform::GetRotation() const
	{
		return glm::eulerAngles(m_orientation);
	}

	glm::quat Transform::GetQuaternionRotation() const
	{
		return m_orientation;
	}

	glm::vec3  Transform::GetScale() const
	{
		return m_scale;
	}

	glm::vec3 Transform::Right() const
	{
		return m_orientation * glm::vec3(1, 0, 0);
	}

	glm::vec3 Transform::Up() const
	{
		return m_orientation * glm::vec3(0, 1, 0);
	}

	glm::vec3 Transform::Forward() const
	{
		return m_orientation * glm::vec3(0, 0, -1);
	}

	glm::mat4 Transform::GetModelMatrix() 
	{
		// Transform properties have changed. We need to regenerate model matrix.
		if (m_dirty) 
		{
			m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
			m_dirty = false;
		}

		return m_modelMatrix;
	}
}