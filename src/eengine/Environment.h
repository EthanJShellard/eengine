#include <gl/glew.h>

#include <string>
#include <chrono>

namespace eengine 
{
	// Engine forward declarations
	class Core;

	class Environment 
	{
		friend class Core;

	private:
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float>> m_lastTime;

		float m_deltaTime;
		
		std::string m_projectWorkingDirectory;

		Environment();
		void OnFrameStart();
	public:
		float GetDeltaTime();
		std::string GetProjectWorkingDirectory();
	};
}