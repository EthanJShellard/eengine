#include <list>

#include "eengine_defines.h"

namespace eengine
{
	// Engine Forward Declarations
	class Environment;
	class Input;
	class Entity;

	class Core
	{
	private:
		Core();

		shared<Environment> m_environment;
		std::list<shared<Entity>> m_entities;
		shared<Input> m_input;
		weak<Core> m_self;

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