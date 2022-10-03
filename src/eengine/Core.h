#ifndef EENGINE_CORE
#define EENGINE_CORE

#include <vector>

#include "eengine_defines.h"
#include "Entity.h"

// Forward Declarations
class Environment;
class Input;
class Entity;

namespace eengine
{
	class Core
	{
	private:
		// Private Functions
		Core();
		// Private Members
		shared<Environment> environment;
		std::vector<shared<Entity>> entities;
		shared<Input> input;

		bool m_running;
	public:
		//Public Functions
		static void TestFunction();

		static shared<Core> Initialise();
		void Start();
		void Stop();
		shared<Entity> AddEntity();
	};
}
#endif // !EENGINE_CORE