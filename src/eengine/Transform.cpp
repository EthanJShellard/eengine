#include "Transform.h"

namespace eengine 
{
	void Transform::SetPosition(glm::vec3 _newPos) 
	{
		m_position = _newPos;
	}

	void  Transform::SetPosition(float _x, float _y, float _z)
	{
		m_position = glm::vec3(_x, _y, _z);
	}

	void  Transform::SetRotation(glm::vec3 _newRot)
	{
		m_orientation = glm::quat(_newRot);
	}

	void  Transform::SetRotation(float _x, float _y, float _z)
	{
		m_orientation = glm::quat(glm::vec3(_x, _y, _z));
	}

	void Transform::SetRotation(glm::quat _newRot)
	{
		m_orientation = _newRot;
	}

	void  Transform::SetScale(glm::vec3 _newScale)
	{
		m_scale = _newScale;
	}

	void  Transform::SetScale(float _x, float _y, float _z)
	{
		m_scale = glm::vec3(_x, _y, _z);
	}

	void  Transform::Rotate(float _angle, glm::vec3 _axis)
	{
		m_orientation = glm::angleAxis(glm::radians(_angle), _axis) * m_orientation;
	}

	void  Transform::Translate(glm::vec3 _move)
	{
		m_position += _move;
	}

	void Transform::Scale(glm::vec3 _scaleFactors) 
	{
		m_scale *= _scaleFactors;
	}

	glm::vec3  Transform::GetPosition()
	{
		return m_position;
	}

	glm::vec3  Transform::GetRotation()
	{
		return glm::eulerAngles(m_orientation);
	}

	glm::quat Transform::GetQuaternionRotation()
	{
		return m_orientation;
	}

	glm::vec3  Transform::GetScale()
	{
		return m_scale;
	}

	glm::vec3 Transform::Right()
	{
		return m_orientation * glm::vec3(1, 0, 0);
	}

	glm::vec3 Transform::Up()
	{
		return m_orientation * glm::vec3(0, 1, 0);
	}

	glm::vec3 Transform::Forward()
	{
		return m_orientation * glm::vec3(0, 0, 1);
	}
}