#ifndef EENGINE_ENTITY
#define EENGINE_ENTITY

#include <vector>

#include "eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class Component;
	class Core;

	class Entity 
	{
		friend class Core;
	private:
		void Tick();
		void Display();

		std::vector<shared<Component>> m_components;
		weak<Core> m_core;
		weak<Entity> m_self;
	public:
		shared<Core> GetCore();

		template<typename T >
		shared<T> AddComponent();
		template<typename T, typename A>
		shared<T> AddComponent(A _a);
		template<typename T, typename A, typename B>
		shared<T> AddComponent(A _a, B _b);
		template<typename T, typename A, typename B, typename C>
		shared<T> AddComponent(A _a, B _b, C _c);
	};
}
#endif // !EENGINE_ENTITY