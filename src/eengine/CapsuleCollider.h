#include "Collider.h"

namespace eengine 
{
	/// @brief A capsule-shaped collider which can be added to a RigidBody.
	class CapsuleCollider : public Collider 
	{
	public:
		/// @brief Create a capsule-shaped collider.
		/// @param _radius The radius of the capsule ends.
		/// @param _height The height of the middle section between the ends.
		CapsuleCollider(float _radius, float _height);
	};
}