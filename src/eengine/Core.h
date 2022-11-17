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
	class Resources;
	class RenderContext;
	class AudioContext;

	/// @brief The central structure responsible for the operation of eengine.
	class Core : private NonCopyable
	{
	private:
		Core();

		shared<Environment> m_environment;
		std::list<shared<Entity>> m_entities;
		shared<Input> m_input;
		weak<Core> m_self;
		shared<Camera> m_mainCamera;
		shared<RenderContext> m_renderContext;
		shared<Resources> m_resources;
		shared<AudioContext> m_audioContext;

		SDL_Window* m_window;
		bool m_running;
	public:
		~Core();

		/// @brief Instantiate and initialise an instance of eengine.
		/// @param _projectWorkingDirectory A path to the program executable. For C++, the first program argument can be used.
		/// @return A shared pointer the the newly created Core.
		static shared<Core> Initialise(const char* _projectWorkingDirectory);

		/// @brief Begin execution of the main engine loop.
		void Start();

		/// @brief Flag that the main engine loop should stop at the end of this frame.
		void Stop();

		/// @brief Instantiate a new Entity.
		/// @return A shared pointer to the newly created Entity.
		shared<Entity> AddEntity();

		/// @brief Get the engine Environment.
		/// @return A shared pointer to the engine Environment.
		shared<Environment> GetEnvironment();

		/// @brief Get the main Camera.
		/// @return A shared pointer to the main Camera.
		shared<Camera> GetMainCamera();

		/// @brief Get the engine Input object.
		/// @return A shared pointer to the engine Input object.
		shared<Input> GetInput();

		/// @brief Get the engine Resources object.
		/// @return A shared pointer to the engine Resources object.
		shared<Resources> GetResources();
	};
}