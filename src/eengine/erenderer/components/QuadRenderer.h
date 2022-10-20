#include "../../Component.h"
#include "../../eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class Mesh;
	class Shader;

	class QuadRenderer : public Component
	{
		shared<Mesh> m_mesh;
		shared<Shader> m_shader;

		void OnDisplay();
		QuadRenderer();
	};
}