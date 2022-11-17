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
	class RenderContext;

	/// @brief The Component super-class. Inherit from this to add behavior to eengine Entity.
	class Component : public NonCopyable
	{
		friend class Entity;
	private:		
		/// @brief Called just before OnTick is called for the first time. 
		virtual void OnBegin();
		
		/// @brief Called once each frame before rendering, if the parent Entity and Component are enabled.
		virtual void OnTick();
		
		/// @brief Called once each frame, after the state has finished updating and we are ready to draw.
		/// @param _renderer The default renderer, available to all components.
		virtual void OnDisplay(shared<RenderContext> _renderContext);

		/// @breif Called to get the type name of this component. Use the NAME(T) macro to define this function in your components.
		/// @return The type name of this component.
		virtual const char* GetName() const = 0;

		// Cache references to prevent having to repeatedly climb the hierarchy.
		weak<Entity> m_parent;
		weak<Core> m_core;
		weak<Input> m_input;
	public:
		/// @brief Called just after component is instantiated and provided with references to its parent, the engine Core and engine Input.
		/// Do not call manually
		virtual void OnInit();

		/// @brief Get a shared pointer to the Entity which owns this component.
		/// @return A shared pointer to the Entity which owns this component.
		shared<Entity> GetParent();

		/// @brief Get a shared pointer to the engine Core.
		/// @return A shared pointer to the engine Core.
		shared<Core> GetCore();

		/// @brief Get a shared pointer to the engine Input object.
		/// @return A shared pointer to the engine Input object.
		shared<Input> GetInput();
	};
}
#endif // EENGINE_COMPONENT