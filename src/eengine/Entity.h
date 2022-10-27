#include <vector>

#include "eengine_defines.h"
#include "NonCopyable.h"
#include "components/Transform.h"

namespace rend 
{
	struct Renderer;
}

namespace eengine 
{
	// Engine forward declarations
	class Component;
	class Core;

	/// @brief A game object class which contains Components. All objects in eengine consist of an Entity with Component children.
	class Entity : private NonCopyable
	{
		friend class Core;
	private:
		Entity();

		void Tick();
		void Display(shared<rend::Renderer> _renderer);

		std::vector<shared<Component>> m_components;
		weak<Core> m_core;
		weak<Entity> m_self;

		shared<Transform> m_transform;

		bool m_destroyed;
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
	};


	template<typename T>
	shared<T> Entity::AddComponent()
	{
		auto share = std::make_shared<T>();
		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_components.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A>
	shared<T> Entity::AddComponent(A _a)
	{
		auto share = std::make_shared<T>(_a);
		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_components.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A, typename B>
	shared<T> Entity::AddComponent(A _a, B _b)
	{
		auto share = std::make_shared<T>(_a, _b);
		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_components.push_back(share);
		share->OnInit();
		return share;
	}

	template<typename T, typename A, typename B, typename C>
	shared<T> Entity::AddComponent(A _a, B _b, C _c)
	{
		auto share = std::make_shared<T>(_a, _b, _c);
		share->m_parent = m_self;
		share->m_core = m_core;
		share->m_input = m_core.lock()->GetInput();
		m_components.push_back(share);
		share->OnInit();
		return share;
	}
}