#include "Component.h"
#include "RenderContext.h"

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

	void Component::OnDisplay(shared<RenderContext> _renderContext)
	{
		// Stub
	}

	void Component::OnRemove() 
	{
		// Stub
	}
}