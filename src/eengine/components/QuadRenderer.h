#include <rend/rend.h>

#include "../eengine_defines.h"
#include "../Component.h"

namespace eengine 
{
	class QuadRenderer : public Component 
	{
	private:
		rend::Mesh m_mesh;
		rend::Shader m_shader;

		void OnDisplay();
	public:
		QuadRenderer();
	};
}