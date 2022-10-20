#include "Camera.h"
#include "components/Transform.h"

namespace eengine 
{
	Camera::Camera(float _vertFov, float _near, float _far, shared<Transform> _transform)
	{
		m_vFOV = _vertFov;
		m_near = _near;
		m_far = _far;
		m_transform = _transform;
	}

	Camera::Camera()
	{
		m_vFOV = 45.0f;
		m_near = 0.1f;
		m_far = 100.0f;
		m_transform = std::make_shared<Transform>();
	}
}