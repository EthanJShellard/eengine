#include "Collider.h"


namespace eengine 
{
	class BoxCollider : public Collider 
	{
		
	public:

		/// @brief Create a box shaped collider.
		/// @param _halfWidth Half the width of the box.
		/// @param _halfHeight Half the height of the box.
		/// @param _halfDepth half the depth of the box.
		BoxCollider(float _halfWidth, float _halfHeight, float _halfDepth);
	};
}