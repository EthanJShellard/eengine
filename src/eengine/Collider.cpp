#include "Collider.h"

namespace eengine 
{
	Collider::Collider() 
	{
		m_transform = std::make_shared<btTransform>();
		m_transform->setIdentity();
	}
}