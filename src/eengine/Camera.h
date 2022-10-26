#include "eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class Transform;

	/// @brief A simple wrapper class for Camera data.
	class Camera
	{
	public:
		/// @brief Vertical field of view, degrees.
		float m_vFOV;
		/// @brief Distance to the near plane.
		float m_near;
		/// @brief Distance to the far plane.
		float m_far;
		/// @brief This camera's transform.
		shared<Transform> m_transform;

		/// @brief Detailed constructor for a Camera.
		/// @param _vFOV Vertical field of view, degrees.
		/// @param _near Distance to the near plane.
		/// @param _far Distance to the far plane.
		Camera(float _vFOV, float _near, float _far);

		/// @brief Default Camera constructor.
		/// @details Vertical FOV defaults to 45 degrees, near plane distance defaults to 0.1f and the far plane distance defaults to 1000.0f.
		Camera();
	};
}