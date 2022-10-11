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
		rtn->self = rtn;
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
		// STUB
		return std::make_shared<Entity>();
	}
}

