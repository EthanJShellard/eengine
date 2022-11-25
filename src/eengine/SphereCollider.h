#include "Collider.h"

namespace eengine 
{
	class SphereCollider : public Collider 
	{
	public:

		/// @brief Create a sphere shaped collider.
		/// @param _radius The radius of the sphere.
		SphereCollider(float _radius);
	};
}