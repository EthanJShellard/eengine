#include "Collider.h"

namespace eengine 
{
	/// @brief A sphere-shaped collider which can be attached to a RigidBody.
	class SphereCollider : public Collider 
	{
	public:

		/// @brief Create a sphere shaped collider.
		/// @param _radius The radius of the sphere.
		SphereCollider(float _radius);
	};
}