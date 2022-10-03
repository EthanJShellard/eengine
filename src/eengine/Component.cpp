#include "Component.h"

namespace eengine
{
	shared<Entity> Component::GetParent()
	{
		return parent.lock();
	}

	shared<Core> Component::GetCore() 
	{
		return core.lock();
	}

	shared<Input> Component::GetInput() 
	{
		return input.lock();
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

	void Component::OnDisplay() 
	{
		// Stub
	}
}