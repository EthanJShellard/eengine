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