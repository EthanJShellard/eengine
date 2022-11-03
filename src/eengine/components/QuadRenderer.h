#include <rend/rend.h>

#include "../eengine_defines.h"
#include "../Component.h"

namespace eengine 
{
	/// @brief Component which will render a quad at the location of its parent.
	COMPONENT(QuadRenderer)
	{	
	private:
		rend::Mesh m_mesh;
		shared<rend::Shader> m_shader;
		shared<rend::Texture> m_texture;
		glm::vec4 m_colour;

		void OnTick();
		void OnDisplay(shared<RenderContext> _renderContext);

	public:
		QuadRenderer();
		void OnInit();
		/// @brief Set the colour of the quad.
		/// @param _r The red channel.
		/// @param _g The green channel.
		/// @param _b The blue channel.
		/// @param _a The alpha channel.
		void SetColour(float _r, float _g, float _b, float _a);
	};
}