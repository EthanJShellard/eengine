#include "Entity.h"
#include "Component.h"

namespace eengine 
{
	Entity::Entity() 
	{
		m_destroyed = false;
	}

	void Entity::Tick()
	{
		for (shared<Component> c : m_components)
		{
			c->OnTick();
		}
	}

	void Entity::Display()
	{
		for (shared<Component> c : m_components)
		{
			c->OnDisplay();
		}
	}

	shared<Core> Entity::GetCore() const 
	{
		return m_core.lock();
	}

	void Entity::Destroy() 
	{
		m_destroyed = true;
	}

	bool Entity::IsDestroyed() const
	{
		return m_destroyed;
	}
}