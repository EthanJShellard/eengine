#ifndef EENGINE_SHADER
#define EENGINE_SHADER

#include <rend/Shader.h>

#include "Resource.h"


namespace eengine 
{
	// Engine forward declarations
	class ModelRenderer;
	class QuadRenderer;

	/// @brief eengine wrapper for Shader resources.
	class Shader : public Resource 
	{
		friend class Resources;
		friend class ModelRenderer;
		friend class QuadRenderer;
	private:
		std::string m_vertPath;
		std::string m_fragPath;

		shared<rend::Shader> m_rendShader;

		/// @brief Get the rend representation of this Model. Only available if rend is being used.
		/// @return A shared pointer to the rend representation of this Model.
		shared<rend::Shader> GetRendShader();

		void Load();
	public:
		/// @brief Get the relative path this program's vertex shader.
		/// @return A string representing the relative path to this programs vertex shader.
		std::string GetVertPath() const;

		/// @brief Get the relative path this program's fragment shader.
		/// @return A string representing the relative path to this programs fragment shader.
		std::string GetFragPath() const;
	};
}

#endif // EENGINE_SHADER