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
	};
}
#endif // !EENGINE_ENTITY