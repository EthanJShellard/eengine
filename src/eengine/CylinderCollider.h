#include "Collider.h"

namespace eengine 
{
	/// @brief A cylinder-shaped collider which can be added to a RigidBody.
	class CylinderCollider : public Collider 
	{
	public:
		/// @brief Create a cylinder-shaped collider.
		/// @param _width The width of the cylinder.
		/// @param _height The height of the cylinder.
		/// @param _depth The depth of the cylinder.
		CylinderCollider(float _width, float _height, float _depth);
	};
}