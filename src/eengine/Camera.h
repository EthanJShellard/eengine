#include "Transform.h"

namespace eengine 
{
	class Camera 
	{
	public:
		Transform m_transform;
		float m_vFOV;
		float m_near;
		float m_far;

		Camera(float _vFOV, float _near, float _far, Transform _tf);
		Camera();
	};
}