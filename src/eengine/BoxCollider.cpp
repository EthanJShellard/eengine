#include "BoxCollider.h"

namespace eengine 
{
	BoxCollider::BoxCollider(float _halfWidth, float _halfHeight, float _halfDepth)
	{
		m_collisionShape = std::make_shared<btBoxShape>(btVector3(_halfWidth, _halfHeight, _halfDepth));
	}
}