#ifndef EENGINE_COMPONENT
#define EENGINE_COMPONENT

#include <rend/Renderer.h>

#include "eengine_defines.h"
#include "NonCopyable.h"

namespace eengine
{
	//Engine forward declarations
	class Entity;
	class Core;
	class Input;
	class Transform;

	/// @brief The Component super-class. Inherit from this to add behavior to eengine Entity.
	class Component : public NonCopyable
	{
		friend class Entity;
	private:
		/// @brief Called just after component is instantiated and provided with references to its parent, the engine core and engine input.
		virtual void OnInit();
		
		/// @brief Called just before OnTick is called for the first time. 
		virtual void OnBegin();
		
		/// @brief Called once each frame before rendering, if the parent Entity and Component are enabled.
		virtual void OnTick();
		
		/// @brief Called once each frame, after the state has finished updating and we are ready to draw.
		/// @param _renderer The default renderer, available to all components.
		virtual void OnDisplay(shared<rend::Renderer> _renderer);

		// Cache references to prevent having to repeatedly climb the hierarchy.
		weak<Entity> m_parent;
		weak<Core> m_core;
		weak<Input> m_input;
	public:
		/// @brief Get a shared pointer to the Entity which owns this component.
		/// @return A shared pointer to the Entity which owns this component.
		shared<Entity> GetParent();

		/// @brief Get a shared pointer to the engine core.
		/// @return A shared pointer to the engine core.
		shared<Core> GetCore();

		/// @brief Get a shared pointer to the engine input object.
		/// @return A shared pointer to the engine input object.
		shared<Input> GetInput();
	};
}
#endif // EENGINE_COMPONENT