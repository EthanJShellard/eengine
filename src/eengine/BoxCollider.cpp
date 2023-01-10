#include "BoxCollider.h"

namespace eengine 
{
	BoxCollider::BoxCollider(float _width, float _height, float _depth)
	{
		m_collisionShape = std::make_shared<btBoxShape>(btVector3(_width / 2.0f, _height / 2.0f, _depth / 2.0f));
	}
}