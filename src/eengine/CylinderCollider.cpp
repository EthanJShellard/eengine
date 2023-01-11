#include "CylinderCollider.h"

namespace eengine 
{
	CylinderCollider::CylinderCollider(float _width, float _height, float _depth) 
	{
		m_collisionShape = std::make_shared<btCylinderShape>(btVector3(_width / 2.0f, _height / 2.0f, _depth / 2.0f));
	}
}