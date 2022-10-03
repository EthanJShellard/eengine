#ifndef EENGINE_COMPONENT
#define EENGINE_COMPONENT

#include "eengine_defines.h"

// Forward declarations
class Entity;

namespace eengine
{
	class Component
	{
	private:
		weak<Entity> parent;
	public:

	};
}
#endif //! EENGINE_COMPONENT