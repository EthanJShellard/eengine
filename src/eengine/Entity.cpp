#include "Entity.h"

namespace eengine 
{
	shared<Core> Entity::GetCore() 
	{
		return core.lock();
	}

	void Entity::Tick() 
	{
		// Stub
	}

	void Entity::Display() 
	{
		// Stub
	}
}