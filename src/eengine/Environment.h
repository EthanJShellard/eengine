#ifndef EENGINE_ENVIRONMENT
#define EENGINE_ENVIRONMENT

#include <string>
#include <chrono>

namespace eengine 
{
	// Engine forward declarations
	class Core;

	/// @brief Class which provides information about the environment surrounding the engine.
	class Environment 
	{
		friend class Core;

	private:
		std::chrono::steady_clock::time_point m_lastTime;
		float m_deltaTime;
		std::string m_projectWorkingDirectory;

		Environment();

		/// @brief Called at the beginning of each frame to prepare environment data.
		void OnFrameStart();
	public:
		/// @brief Get the time between the start of this frame and the start of the last frame.
		/// @return The time between the start of this frame and the start of the last frame in seconds.
		float GetDeltaTime() const;

		/// @brief Get the path to the project working directory, where the executable can be found.
		/// @return The path to the project working directory as an std::string.
		std::string GetProjectWorkingDirectory() const;
	};
}

#endif // EENGINE_ENVIRONMENT