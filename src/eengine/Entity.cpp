#include <rend/Renderer.h>

#include <stdexcept>
#include <sstream>

#include "Entity.h"
#include "Component.h"
#include "Debug.h"
#include "Core.h"

namespace eengine 
{
	Entity::Entity() 
	{
		m_destroyed = false;
	}

	void Entity::Tick(float _deltaTime)
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
			c->OnTick(_deltaTime);
		}
	}

	void Entity::LateTick(float _deltaTime) 
	{
		// Update components
		for (shared<Component> c : m_components)
		{
			c->OnLateTick(_deltaTime);
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

	void Entity::RemoveComponent(shared<Component> _component) 
	{
		auto itr = std::find(m_components.begin(), m_components.end(), _component);
		if (itr != m_components.end()) 
		{
			(*itr)->OnRemove();
			m_components.erase(itr);
		}
		else 
		{
			throw std::exception();
		}

		auto newCmp = std::find(m_newComponents.begin(), m_newComponents.end(), _component);
		if (newCmp != m_newComponents.end())
		{
			m_newComponents.erase(newCmp);
		}
	}
}