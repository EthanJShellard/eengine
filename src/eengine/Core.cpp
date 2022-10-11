#include <iostream>

#include "Core.h"

namespace eengine
{
	void Core::TestFunction()
	{
		std::cout << "Test Function Success!!" << std::endl;
	}
	
	Core::Core() 
	{
		m_running = false;
	}

	shared<Core> Core::Initialise() 
	{
		// std::make_shared cannot access private constructor, so call it manually
		shared<Core> rtn = shared<Core>(new Core());

		rtn->m_self = rtn;

		return rtn;
	}

	void Core::Start() 
	{
		// STUB
	}

	void Core::Stop() 
	{
		// STUB
	}

	shared<Entity> Core::AddEntity() 
	{
		shared<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = m_self;
		m_entities.push_back(rtn);

		return rtn;
	}
}

