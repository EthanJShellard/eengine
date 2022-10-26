#include <rend/rend.h>

#include "../eengine_defines.h"
#include "../Component.h"

namespace eengine 
{
	/// @brief Component which will render a quad at the location of its parent.
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

		/// @brief Set the colour of the quad.
		/// @param _r The red channel.
		/// @param _g The green channel.
		/// @param _b The blue channel.
		/// @param _a The alpha channel.
		void SetColour(float _r, float _g, float _b, float _a);
	};
}