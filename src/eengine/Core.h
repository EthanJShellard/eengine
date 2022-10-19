#include <list>

#include "eengine_defines.h"
#include "NonCopyable.h"

// Forward declarations
class SDL_Window;

namespace eengine
{
	// Engine Forward Declarations
	class Environment;
	class Input;
	class Entity;

	class Core : private NonCopyable
	{
	private:
		Core();

		shared<Environment> m_environment;
		std::list<shared<Entity>> m_entities;
		shared<Input> m_input;
		weak<Core> m_self;

		SDL_Window* m_window;
		bool m_running;
	public:
		~Core();
		static void TestFunction();

		static shared<Core> Initialise();
		void Start();
		void Stop();
		shared<Entity> AddEntity();
	};
}