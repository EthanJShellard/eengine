#include <rend/Renderer.h>

#include <stdexcept>
#include <sstream>

#include "components/RigidBody.h"
#include "Entity.h"
#include "Component.h"
#include "Debug.h"
#include "Core.h"

namespace eengine 
{
	Entity::Entity() :
		m_enabled(true),
		m_destroyed(false)
	{
	}

	void Entity::Tick(float _deltaTime)
	{
		if (!m_enabled) return;

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
		if (!m_enabled) return;

		// Update components
		for (shared<Component> c : m_components)
		{
			c->OnLateTick(_deltaTime);
		}
	}

	void Entity::Display(shared<RenderContext> _renderContext)
	{
		if (!m_enabled) return;

		for (shared<Component> c : m_components)
		{
			c->OnDisplay(_renderContext);
		}
	}

	void Entity::OnTriggerEnter(shared<RigidBody> _other) 
	{
		for (shared<Component> c : m_components) 
		{
			c->OnTriggerEnter(_other);
		}
	}

	void Entity::OnTriggerExit(shared<RigidBody> _other) 
	{
		for (shared<Component> c : m_components)
		{
			c->OnTriggerExit(_other);
		}
	}

	void Entity::OnCollisionEnter(shared<RigidBody> _other) 
	{
		for (shared<Component> c : m_components)
		{
			c->OnCollisionEnter(_other);
		}
	}

	void Entity::OnCollisionExit(shared<RigidBody> _other)
	{
		for (shared<Component> c : m_components)
		{
			c->OnCollisionExit(_other);
		}
	}

	void Entity::OnDelete() 
	{
		for (shared<Component> c : m_components)
		{
			c->OnDelete();
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

	void Entity::Enable()
	{
		m_enabled = true;

		// Make sure RigidBodies are also enabled
		auto rbs = GetComponentsOfType<RigidBody>();
		for (shared<RigidBody> rb : rbs)
		{
			rb->SetIsEnabled(true);
		}
	}

	void Entity::Disable() 
	{
		m_enabled = false;

		// Make sure RigidBodies are also disabled
		auto rbs = GetComponentsOfType<RigidBody>();
		for (shared<RigidBody> rb : rbs)
		{
			rb->SetIsEnabled(false);
		}
	}

	bool Entity::GetEnabled() const 
	{
		return m_enabled;
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