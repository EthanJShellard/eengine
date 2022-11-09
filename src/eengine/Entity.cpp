#include <rend/Renderer.h>

#include <stdexcept>
#include <sstream>

#include "Entity.h"
#include "Component.h"
#include "Debug.h"

namespace eengine 
{
	Entity::Entity() 
	{
		m_destroyed = false;
	}

	void Entity::Tick()
	{
		for (shared<Component> c : m_components)
		{
			try 
			{
				c->OnTick();
			}
			catch (std::runtime_error e)
			{
				std::stringstream sStream;
				sStream << e.what() << " : " << c->GetName();
				Debug::Log(sStream.str());
				Destroy();
			}
			catch (std::exception e)
			{
				std::stringstream sStream;
				sStream << e.what() << " : " << c->GetName();
				Debug::Log(sStream.str());
				Destroy();
			}
			catch (...)
			{
				std::stringstream sStream;
				sStream << "Caught unknown exception! : " << c->GetName();
				Debug::Log(sStream.str());
				Destroy();
			}
		}
	}

	void Entity::Display(shared<RenderContext> _renderContext)
	{
		for (shared<Component> c : m_components)
		{
			c->OnDisplay(_renderContext);
		}
	}

	shared<Core> Entity::GetCore() const 
	{
		return m_core.lock();
	}

	shared<Transform> Entity::GetTransform() const 
	{
		return m_transform;
	}

	void Entity::Destroy() 
	{
		m_destroyed = true;
	}

	bool Entity::IsDestroyed() const
	{
		return m_destroyed;
	}
}