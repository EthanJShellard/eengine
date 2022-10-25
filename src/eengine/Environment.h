#include <gl/glew.h>

#include <string>

namespace eengine 
{
	// Engine forward declarations
	class Core;

	class Environment 
	{
		friend class Core;

	private:
		float m_deltaTime;
		GLuint m_lastTime;
		std::string m_projectWorkingDirectory;

		Environment();
		void OnFrameStart();
	public:
		float GetDeltaTime();
		std::string GetProjectWorkingDirectory();
	};
}