#include <list>
#include <vector>
#include <algorithm>

#include "eengine_defines.h"
#include "NonCopyable.h"
#include "components/Transform.h"
#include "Core.h"

namespace rend 
{
	struct Renderer;
}

namespace eengine 
{
	// Engine forward declarations
	class Component;
	class RenderContext;
	class RigidBody;
	class PhysicsContext;

	/// @brief A game object class which contains Components. All objects in eengine consist of an Entity with Component children.
	class Entity : private NonCopyable
	{
		friend class Core;
		friend class PhysicsContext;
	private:
		Entity();

		/// @brief Update all components,
		/// @param _deltaTime The time in seconds since the last frame.
		void Tick(float _deltaTime);

		/// @brief Update all components after engine physics has been updated.
		/// @param _deltaTime The time in seconds since the last frame.
		void LateTick(float _deltaTime);

		/// @brief Render all renderable components.
		/// @param _renderContext The engine render context.
		void Display(shared<RenderContext> _renderContext);

		/// @brief Called when a collider enters this Entity's trigger.
		/// @param _other The RigidBody of the collider which entered the trigger.
		void OnTriggerEnter(shared<RigidBody> _other);

		/// @brief Called when a collider exits this Entity's trigger.
		/// @param _other The RigidBody of the collider which exited the trigger.
		void OnTriggerExit(shared<RigidBody> _other);

		/// @brief Called when a collider enters this Entity's collider.
		/// @param _other The RigidBody of the collider which entered the collider.
		void OnCollisionEnter(shared<RigidBody> _other);

		/// @brief Called when a collider exits this Entity's collider.
		/// @param _other The RigidBody of the collider which exited the collider.
		void OnCollisionExit(shared<RigidBody> _other);

		/// @brief Called just before the entity is about to be removed from the scene. This should cause deletion of the Entity, if no strong references remain.
		void OnDelete();

		std::list<shared<Component>> m_components;
		std::list<shared<Component>> m_newComponents;
		weak<Core> m_core;
		weak<Entity> m_self;

		shared<Transform> m_transform;

		bool m_destroyed;
		bool m_enabled;
	public:
		/// @brief Get the engine Core.
		/// @return A shared pointer to the engine Core.
		shared<Core> GetCore() const;

		/// @brief All standard Entities start with a transform component. This gets a cached reference to that component.
		/// @return The transform component of this entity
		shared<Transform> GetTransform() const;

		/// @brief Flag this entity for destruction at the end of this update.
		void Destroy();

		/// @brief Check if this Entity has been flagged for destruction. This does not refer to whether this Entity is actually destroyed.
		/// @return The state of the destruction flag.
		bool IsDestroyed() const;

		/// @brief Enable this Entity, allowing updates and events for its components.
		/// @details Will call OnEnable() on all child components.
		void Enable();

		/// @brief Disable this Entity, disallowing updates and events for its components.
		/// @details Will call OnDisable() on all child components.
		void Disable();

		/// @brief Get whether or not this Entity has been disabled.
		/// @return Whether or not this Entity has been disabled.
		bool GetEnabled() const;

		/// @brief Instantiate and add a Component to this Entity.
		/// @tparam T The type of Component to add.
		/// @return A shared pointer to the newly created Component.
		template<typename T>
		shared<T> AddComponent();

		/// @brief Instantiate and add a Component to this Entity.
		/// @tparam T The type of Component to add.
		/// @tparam A The type of the first constructor parameter for a Component of type T.
		/// @param _a The first constructor paramter for a Component of type T.
		/// @return A shared pointer to the newly created Component.
		template<typename T, typename A>
		shared<T> AddComponent(A _a);

		/// @brief Instantiate and add a Component to this Entity.
		/// @tparam T The type of Component to add.
		/// @tparam A The type of the first constructor parameter for a Component of type T.
		/// @tparam B The type of the second constructor parameter for a Component of type T.
		/// @param _a The first constructor paramter for a Component of type T.
		/// @param _b The second constructor paramter for a Component of type T.
		/// @return A shared pointer to the newly created Component.
		template<typename T, typename A, typename B>
		shared<T> AddComponent(A _a, B _b);

		/// @brief @brief Instantiate and add a Component to this Entity.
		/// @tparam T The type of Component to add.
		/// @tparam A The type of the first constructor parameter for a Component of type T.
		/// @tparam B The type of the second constructor parameter for a Component of type T.
		/// @tparam C The type of the third constructor parameter for a Component of type T.
		/// @param _a The first constructor paramter for a Component of type T.
		/// @param _b The second constructor paramter for a Component of type T.
		/// @param _c The third constructor paramter for a Component of type T.
		/// @return A shared pointer to the newly created Component.
		template<typename T, typename A, typename B, typename C>
		shared<T> AddComponent(A _a, B _b, C _c);

		/// @brief Get the first Component of type T found on this Entity. Will return nullptr if no such component exists.
		/// @tparam T The type of Component to get.
		/// @return The Component.
		template<typename T>
		shared<T> GetComponentOfType();

		/// @brief Get a vector of Components with type T attached to this Entity. Can return an empty vector.
		/// @tparam T The type of Component to get.
		/// @return A list of the found Components.
		template<typename T>
		std::vector<shared<T>> GetComponentsOfType();

		/// @brief Remove the first Component of type T on this Entity. Can throw an exception if no such Component is found.
		/// @tparam T The type of Component to remove.
		template<typename T>
		void RemoveComponentOfType();

		/// @brief Remove all Components of type T from this Entity.
		/// @tparam T The type of Component to remove.
		template<typename T>
		void RemoveComponentsOfType();

		/// @brief Remove the parameter Component from this Entity. Will return nullptr if the Component is not present on this Entity.
		/// @param _component The Component to remove.
		void RemoveComponent(shared<Component> _component);
	};


	template<typename T>
	shared<T> Entity::AddComponent()
	{
		auto share = std::make_shared<T>();

		if (share->NeedsUniqueness()) 
		{
			if (GetComponentOfType<T>()) 
			{
				throw std::runtime_error("Attempted to add multiple components of a type which requires uniqueness!!");
			}
		}

		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_newComponents.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A>
	shared<T> Entity::AddComponent(A _a)
	{
		auto share = std::make_shared<T>(_a);

		if (share->NeedsUniqueness())
		{
			if (GetComponentOfType<T>())
			{
				throw std::runtime_error("Attempted to add multiple components of a type which requires uniqueness!!");
			}
		}

		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_newComponents.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A, typename B>
	shared<T> Entity::AddComponent(A _a, B _b)
	{
		auto share = std::make_shared<T>(_a, _b);

		if (share->NeedsUniqueness())
		{
			if (GetComponentOfType<T>())
			{
				throw std::runtime_error("Attempted to add multiple components of a type which requires uniqueness!!");
			}
		}

		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_newComponents.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A, typename B, typename C>
	shared<T> Entity::AddComponent(A _a, B _b, C _c)
	{
		auto share = std::make_shared<T>(_a, _b, _c);

		if (share->NeedsUniqueness())
		{
			if (GetComponentOfType<T>())
			{
				throw std::runtime_error("Attempted to add multiple components of a type which requires uniqueness!!");
			}
		}

		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_newComponents.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T>
	shared<T> Entity::GetComponentOfType() 
	{
		for (shared<Component> c : m_components) 
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(c);
			if (ptr) 
			{
				return ptr;
			}
		}

		for (shared<Component> c : m_newComponents)
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(c);
			if (ptr)
			{
				return ptr;
			}
		}

		return nullptr;
	}

	template<typename T>
	std::vector<shared<T>> Entity::GetComponentsOfType() 
	{
		std::vector<shared<T>> componentsFound;
		for (shared<Component> c : m_components) 
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(c);
			if (ptr) 
			{
				componentsFound.push_back(ptr);
			}
		}

		for (shared<Component> c : m_newComponents)
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(c);
			if (ptr)
			{
				componentsFound.push_back(ptr);
			}
		}

		return componentsFound;
	}

	template<typename T>
	void Entity::RemoveComponentOfType()
	{
		auto itr = m_components.begin();

		while (itr != m_components.end()) 
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(*itr);
			if (ptr) 
			{
				m_components.erase(itr);
				return;
			}
			itr++;
		}

		itr = m_newComponents.begin();
		while (itr != m_components.end()) 
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(*itr);
			if (ptr)
			{
				m_newComponents.erase(itr);
				return;
			}
			itr++;
		}

		throw std::exception();
	}

	template<typename T>
	void Entity::RemoveComponentsOfType() 
	{
		auto itr = m_components.begin();

		while (itr != m_components.end())
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(*itr);
			if (ptr)
			{
				itr = m_components.erase(itr);
			}
			else 
			{
				itr++;
			}
		}

		auto newCmp = m_newComponents.begin();

		while (newCmp != m_newComponents.end()) 
		{
			shared<T> ptr = std::dynamic_pointer_cast<T>(*newCmp);
			if (ptr)
			{
				newCmp = m_newComponents.erase(newCmp);
			}
			else
			{
				newCmp++;
			}
		}
	}
}