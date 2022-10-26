#include <list>

#include "eengine_defines.h"
#include "NonCopyable.h"

// Forward declarations
struct SDL_Window;

namespace rend
{
	struct Renderer;
}

namespace eengine
{
	// Engine Forward Declarations
	class Environment;
	class Input;
	class Entity;
	class Camera;

	class Core : private NonCopyable
	{
	private:
		Core();

		shared<Environment> m_environment;
		std::list<shared<Entity>> m_entities;
		shared<Input> m_input;
		weak<Core> m_self;
		shared<Camera> m_mainCamera;
		shared<rend::Renderer> m_mainRenderer;

		SDL_Window* m_window;
		bool m_running;
	public:
		~Core();

		static shared<Core> Initialise(const char* _projectWorkingDirectory);
		void Start();
		void Stop();
		shared<Entity> AddEntity();
		shared<Environment> GetEnvironment();
		shared<Camera> GetMainCamera();
	};
}