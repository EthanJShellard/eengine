#include <iostream>

#include "Debug.h"

namespace eengine 
{
	void Debug::Log(const char* _str) 
	{
		std::cout << _str << std::endl;
	}
}