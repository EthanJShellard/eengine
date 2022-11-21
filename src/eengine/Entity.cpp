#include <rend/Renderer.h>

#include <stdexcept>
#include <sstream>

#include "Entity.h"
#include "Component.h"
#include "Debug.h"

namespace eengine 
{
	Entity::Entity() 
	{
		m_destroyed = false;
	}

	void Entity::Tick()
	{
		// Call OnBegin on newly added components
		if (!m_newComponents.empty()) 
		{
			for (shared<Component> c : m_newComponents)
			{
				c->OnBegin();
			}
			m_newComponents.clear();
		}

		// Update components
		for (shared<Component> c : m_components)
		{
			c->OnTick();
		}
	}

	void Entity::Display(shared<RenderContext> _renderContext)
	{
		for (shared<Component> c : m_components)
		{
			c->OnDisplay(_renderContext);
		}
	}

	shared<Core> Entity::GetCore() const 
	{
		return m_core.lock();
	}

	shared<Transform> Entity::GetTransform() const 
	{
		return m_transform;
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