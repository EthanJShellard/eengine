#include "Collider.h"

namespace eengine 
{
	class CapsuleCollider : public Collider 
	{
	public:
		CapsuleCollider(float _radius, float _height);
	};
}