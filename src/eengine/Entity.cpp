#include "Entity.h"
#include "Component.h"

namespace eengine 
{
	shared<Core> Entity::GetCore() 
	{
		return m_core.lock();
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

	template<typename T>
	shared<T> Entity::AddComponent() 
	{
		auto share = std::make_shared<T>();
		components.push_back(share);
		return share;
	}

	template<typename T, typename A>
	shared<T> Entity::AddComponent(A _a) 
	{
		auto share = std::make_shared<T>(_a);
		components.push_back(share);
		return share;
	}

	template<typename T, typename A, typename B>
	shared<T> Entity::AddComponent(A _a, B _b) 
	{
		auto share = std::make_shared<T>(_a, _b);
		components.push_back(share);
		return share;
	}

	template<typename T, typename A, typename B, typename C>
	shared<T> Entity::AddComponent(A _a, B _b, C _c) 
	{
		auto share = std::make_shared<T>(_a, _b, _c);
		components.push_back(share);
		return share;
	}
}