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
		m_running = true;

		while (m_running) 
		{
			// MAIN ENGINE LOOP
		}
	}

	void Core::Stop() 
	{
		m_running = false;
	}

	shared<Entity> Core::AddEntity() 
	{
		shared<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = m_self;
		rtn->m_self = rtn;
		m_entities.push_back(rtn);

		return rtn;
	}
}

