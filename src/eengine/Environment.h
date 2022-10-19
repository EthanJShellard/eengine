#include <gl/glew.h>

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

		Environment();
		void OnFrameStart();
	public:
		float GetDeltaTime();
	};
}