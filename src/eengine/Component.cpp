#include "Component.h"

namespace eengine
{
	shared<Entity> Component::GetParent()
	{
		return m_parent.lock();
	}

	shared<Core> Component::GetCore() 
	{
		return m_core.lock();
	}

	shared<Input> Component::GetInput() 
	{
		return m_input.lock();
	}

	void Component::OnInit() 
	{
		// Stub
	}

	void Component::OnBegin() 
	{
		// Stub
	}

	void Component::OnTick() 
	{
		// Stub
	}

	void Component::OnDisplay(shared<rend::Renderer> _renderer) 
	{
		// Stub
	}
}