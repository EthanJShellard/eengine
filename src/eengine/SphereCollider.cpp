#include "SphereCollider.h"

namespace eengine 
{
	SphereCollider::SphereCollider(float _radius) 
	{
		m_collisionShape = std::make_shared<btSphereShape>(_radius);
	}
}