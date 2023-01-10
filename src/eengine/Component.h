#ifndef EENGINE_COMPONENT
#define EENGINE_COMPONENT

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
	class RigidBody;

	/// @brief The Component super-class. Inherit from this to add behavior to eengine Entity.
	class Component : public NonCopyable
	{
		friend class Entity;
	private:		
		/// @brief Called just before OnTick is called for the first time. 
		virtual void OnBegin();
		
		/// @brief Called once each frame before rendering, if the parent Entity and Component are enabled.
		/// @param _deltaTime The time since last frame in seconds.
		virtual void OnTick(float _deltaTime);

		/// @brief Called once each frame, after the physics state has been updated and just before rendering.
		/// @param _deltaTime The time since last frame in seconds.
		virtual void OnLateTick(float _deltaTime);
		
		/// @brief Called once each frame, after the state has finished updating and we are ready to draw.
		/// @param _renderer The default renderer, available to all components.
		virtual void OnDisplay(shared<RenderContext> _renderContext);

		/// @brief Called Just before this Component is to be removed from its parent and then likely deallocated.
		virtual void OnRemove();

		/// @brief Called when this Component's parent's collider is entered by another collider, so long as its RigidBody is set as a trigger.
		/// @param _other The RigidBody which entered this parent's collider.
		virtual void OnTriggerEnter(shared<RigidBody> _other);

		/// @brief Called when this Component's parent's collider is exited by another collider, so long as its RigidBody is set as a trigger.
		/// @param _other The RigidBody which exited the parent's collider
		virtual void OnTriggerExit(shared<RigidBody> _other);

		/// @brief Called when this Component's parent's collider is entered by another non-trigger collider.
		/// @param _other The RigidBody which entered the parent's collider.
		virtual void OnCollisionEnter(shared<RigidBody> _other);

		/// @brief Called when this Component's parent's collider is exited by another non-trigger collider.
		/// @param _other The RigidBody which exited the parent's collider.
		virtual void OnCollisionExit(shared<RigidBody> _other);

		/// @brief Called when the parent object is about to be deleted.
		virtual void OnDelete();

		// Cache references to prevent having to repeatedly climb the hierarchy.
		weak<Entity> m_parent;
		weak<Core> m_core;
		weak<Input> m_input;
	public:
		/// @brief Called just after component is instantiated and provided with references to its parent, the engine Core and engine Input.
		/// Do not call manually
		virtual void OnInit();

		/// @brief Called when attempting to add a Component to an Entity. Override to specify whether or not there
		/// should only ever be one instance of this Component on an Entity. Returns false by default.
		/// @return Whether or not there should only ever be one instance of this component on an Entity.
		virtual bool NeedsUniqueness() const;

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