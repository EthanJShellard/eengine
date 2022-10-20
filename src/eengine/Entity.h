#include <vector>

#include "eengine_defines.h"
#include "NonCopyable.h"
#include "components/Transform.h"

namespace eengine 
{
	// Engine forward declarations
	class Component;
	class Core;

	class Entity : private NonCopyable
	{
		friend class Core;
	private:
		Entity();

		void Tick();
		void Display();

		std::vector<shared<Component>> m_components;
		weak<Core> m_core;
		weak<Entity> m_self;

		bool m_destroyed;
	public:
		Transform transform;

		shared<Core> GetCore() const;
		void Destroy();
		bool IsDestroyed() const;

		template<typename T>
		shared<T> AddComponent();
		template<typename T, typename A>
		shared<T> AddComponent(A _a);
		template<typename T, typename A, typename B>
		shared<T> AddComponent(A _a, B _b);
		template<typename T, typename A, typename B, typename C>
		shared<T> AddComponent(A _a, B _b, C _c);
	};


	template<typename T>
	shared<T> Entity::AddComponent()
	{
		auto share = std::make_shared<T>();
		share->m_parent = m_self;
		m_components.push_back(share);
		return share;
	}

	template<typename T, typename A>
	shared<T> Entity::AddComponent(A _a)
	{
		auto share = std::make_shared<T>(_a);
		share->m_parent = m_self;
		m_components.push_back(share);
		return share;
	}

	template<typename T, typename A, typename B>
	shared<T> Entity::AddComponent(A _a, B _b)
	{
		auto share = std::make_shared<T>(_a, _b);
		share->m_parent = m_self;
		m_components.push_back(share);
		return share;
	}

	template<typename T, typename A, typename B, typename C>
	shared<T> Entity::AddComponent(A _a, B _b, C _c)
	{
		auto share = std::make_shared<T>(_a, _b, _c);
		share->m_parent = m_self;
		m_components.push_back(share);
		return share;
	}
}