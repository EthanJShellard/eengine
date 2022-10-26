#include <rend/rend.h>

#include "../eengine_defines.h"
#include "../Component.h"

namespace eengine 
{
	class QuadRenderer : public Component 
	{
		// SURELY THIS ISN'T NECESSARY?!
		friend class Entity;

	private:
		rend::Mesh m_mesh;
		rend::Shader m_shader;
		glm::vec4 m_colour;

		void OnTick();
		void OnDisplay(shared<rend::Renderer> _renderer);
		void OnInit();
	public:
		QuadRenderer();

		void SetColour(float _r, float _g, float _b, float _a);
	};
}