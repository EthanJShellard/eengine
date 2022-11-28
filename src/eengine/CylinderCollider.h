#include "Collider.h"

namespace eengine 
{
	class CylinderCollider : public Collider 
	{
	public:
		CylinderCollider(float _halfWidth, float _halfHeight, float _halfDepth);
	};
}