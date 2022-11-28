#include "CylinderCollider.h"

namespace eengine 
{
	CylinderCollider::CylinderCollider(float _halfWidth, float _halfHeight, float _halfDepth) 
	{
		m_collisionShape = std::make_shared<btCylinderShape>(btVector3(_halfWidth, _halfHeight, _halfDepth));
	}
}