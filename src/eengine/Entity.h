#ifndef EENGINE_ENTITY
#define EENGINE_ENTITY

#include <vector>

#include "eengine_defines.h"
#include "Core.h"

// Forward declarations
class Component;
class Core;

namespace eengine 
{
	class Entity 
	{
	private:
		std::vector<shared<Component>> components;
		weak<Core> core;
	public:
		shared<Core> GetCore();
		void Tick();
		void Display();

		template<class T >
		shared<T> AddComponent();
		template<class T, class A>
		shared<T> AddComponent(A _a);
		template<class T, class A, class B>
		shared<T> AddComponent(A _a, B _b);
		template<class T, class A, class B, class C>
		shared<T> AddComponent(A _a, B _b, C _c);
	};
}
#endif // !EENGINE_ENTITY