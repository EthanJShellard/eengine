#include "Camera.h"

namespace eengine 
{
	Camera::Camera(float _vertFov, float _near, float _far, Transform _tf)
	{
		m_vFOV = _vertFov;
		m_transform = _tf;
		m_near = _near;
		m_far = _far;
	}

	Camera::Camera()
	{
		m_vFOV = 45.0f;
		m_near = 0.1f;
		m_far = 100.0f;
	}
}