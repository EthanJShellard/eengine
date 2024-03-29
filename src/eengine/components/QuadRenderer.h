#include "../eengine_defines.h"
#include "../Component.h"

#include <rend/Mesh.h>

namespace eengine 
{
	// Engine forward declarations
	class Shader;
	class Texture;
	class Mesh;

	/// @brief Component which will render a quad at the location of its parent.
	class QuadRenderer : public Component
	{	
	private:
		shared<Mesh> m_mesh;
		shared<Shader> m_shader;
		shared<Texture> m_texture;
		glm::vec4 m_colour;

		void OnTick(float _deltaTime);
		void OnDisplay(shared<RenderContext> _renderContext);

	public:
		QuadRenderer();

		/// @brief Called by the engine when this component is first initialised. Do not call this unless you are certain of what you are doing.
		void OnInit();

		/// @brief Set the colour of the quad.
		/// @param _r The red channel.
		/// @param _g The green channel.
		/// @param _b The blue channel.
		/// @param _a The alpha channel.
		void SetColour(float _r, float _g, float _b, float _a);
	};
}