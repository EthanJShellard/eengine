#include "CapsuleCollider.h"

namespace eengine 
{
	CapsuleCollider::CapsuleCollider(float _radius, float _height) 
	{
		m_collisionShape = std::make_shared<btCapsuleShape>(_radius, _height);
	}
}