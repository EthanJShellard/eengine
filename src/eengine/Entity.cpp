#include "Entity.h"

namespace eengine 
{
	shared<Core> Entity::GetCore() 
	{
		return core.lock();
	}

	void Entity::Tick() 
	{
		// Stub
	}

	void Entity::Display() 
	{
		// Stub
	}

	template<class T>
	shared<T> Entity::AddComponent() 
	{
		auto share = std::make_shared<T>();
		components.push_back(share);
		return share;
	}

	template<class T, class A>
	shared<T> Entity::AddComponent(A _a) 
	{
		auto share = std::make_shared<T>(_a);
		components.push_back(share);
		return share;
	}

	template<class T, class A, class B>
	shared<T> Entity::AddComponent(A _a, B _b) 
	{
		auto share = std::make_shared<T>(_a, _b);
		components.push_back(share);
		return share;
	}

	template<class T, class A, class B, class C>
	shared<T> Entity::AddComponent(A _a, B _b, C _c) 
	{
		auto share = std::make_shared<T>(_a, _b, _c);
		components.push_back(share);
		return share;
	}
}