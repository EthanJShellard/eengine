#include "eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class Transform;

	class Camera
	{
	public:
		float m_vFOV;
		float m_near;
		float m_far;
		shared<Transform> m_transform;

		Camera(float _vFOV, float _near, float _far, shared<Transform> _tf);
		Camera();
	};
}