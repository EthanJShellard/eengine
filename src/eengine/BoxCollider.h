#include "Collider.h"


namespace eengine 
{
	/// @brief A box-shaped collider which can be added to a RigidBody.
	class BoxCollider : public Collider 
	{
		
	public:

		/// @brief Create a box-shaped collider.
		/// @param _width The width of the box.
		/// @param _height The height of the box.
		/// @param _depth The depth of the box.
		BoxCollider(float _width, float _height, float _depth);
	};
}