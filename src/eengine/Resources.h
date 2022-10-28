#include <unordered_map>
#include <string>

#include "NonCopyable.h"
#include "eengine_defines.h"

namespace rend
{
	class Shader;
	class Texture;
}


namespace eengine 
{
	class Core;

	/// @brief Class which governs the loading, storing and retrieval of engine resources.
	class Resources : public NonCopyable
	{
		friend class Core;

	private:
		Resources(std::string _projectWorkingDirectory);

		std::unordered_map<std::string, shared<rend::Shader>> m_shaders;
		std::unordered_map<std::string, shared<rend::Texture>> m_textures;

		// Project working directory.
		std::string m_pwd;
	public:
		/// @brief Get a shared pointer to a Shader resource. It will be loaded if it has not yet been.
		/// @param _fragLocation The relative path to the fragment shader.
		/// @param _vertLocation The relative path the the vertex shader.
		/// @return A shared pointer the Shader resource.
		shared<rend::Shader> GetShader(std::string _fragLocation, std::string _vertLocation);

		/// @brief Get a shared pointer to a Texture resource. It will be loaded if it has not yet been.
		/// @param _texLocation The relative path to the Texture.
		/// @return A shared pointer to the Texture resource.
		shared<rend::Texture> GetTexture(std::string _texLocation);
	};
}