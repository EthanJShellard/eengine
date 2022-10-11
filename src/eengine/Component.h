#ifndef EENGINE_COMPONENT
#define EENGINE_COMPONENT

#include "eengine_defines.h"

// Forward declarations
class Entity;
class Core;
class Input;

namespace eengine
{
	class Component
	{
	private:
		virtual void OnInit();
		virtual void OnBegin();
		virtual void OnTick();
		virtual void OnDisplay();

		// Cache references to prevent having to repeatedly climb the hierarchy
		weak<Entity> m_parent;
		weak<Core> m_core;
		weak<Input> m_input;
	public:
		shared<Entity> GetParent();
		shared<Core> GetCore();
		shared<Input> GetInput();
	};
}
#endif //! EENGINE_COMPONENT