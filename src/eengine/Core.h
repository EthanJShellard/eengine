#ifndef EENGINE_CORE
#define EENGINE_CORE

#include <list>

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
		Core();

		shared<Environment> environment;
		std::list<shared<Entity>> entities;
		shared<Input> input;
		weak<Core> self;

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