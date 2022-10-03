#include "Component.h"

namespace eengine
{
	shared<Entity> Component::GetEntity()
	{
		if (auto sharedEntity = parent.lock())
		{
			return sharedEntity;
		}
		else
		{
			// For now!
			throw std::exception();
		}
	}

	shared<Core> Component::GetCore() 
	{
		if (auto sharedCore = core.lock()) 
		{
			return sharedCore;
		}
		else 
		{
			// For now!
			throw std::exception();
		}
	}

	shared<Input> Component::GetInput() 
	{
		if (auto sharedInput = input.lock()) 
		{
			return sharedInput;
		}
		else 
		{
			throw std::exception();
		}
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
}