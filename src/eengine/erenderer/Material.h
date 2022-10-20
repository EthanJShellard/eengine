#include <glm/glm.hpp>

#include "../eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class Texture;
	class Shader;

	class Material 
	{
	private:
		shared<Texture> m_texture;
		shared<Shader> m_shader;

		// Vertex shader uniform locations
		GLint m_modelMatLocation;
		GLint m_viewMatLocation;
		GLint m_projMatLocation;
		// Fragment shader uniform locations
		GLint m_textureLocation;
		GLint m_camPositionLocation;
	public:
		void SetShader(shared<Shader> _newShader);
		void Apply(glm::mat4 _model, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _camPos);

		Material();
	};
}