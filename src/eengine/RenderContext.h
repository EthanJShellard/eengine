#include <rend/rend.h>

#include "eengine_defines.h"
#include "NonCopyable.h"

namespace eengine 
{
	/// @brief Class containing information necessary for rendering in eengine. You can find and manage renderers here.
	class RenderContext : NonCopyable
	{
		friend class Core;

	private:
		shared<rend::Renderer> m_meshRenderer;
		shared<rend::ModelRenderer> m_modelRenderer;

		glm::mat4 m_mainViewMatrix;

		RenderContext();
		void Initialise(int _renderWidth, int _renderHeight);
		void SetMainViewMatrix(const glm::mat4& _newViewMatrix);
		void ClearAll();
	public:
		~RenderContext();

		/// @brief Get the mesh renderer. This is intended for simple meshes, not models (i.e. quads)
		/// @return A shared pointer to the Renderer object.
		shared<rend::Renderer> GetMeshRenderer() const;

		/// @brief Get the model renderer. This is intended for rend Models, not simple meshes.
		/// @return A shared pointer to the ModelRenderer object.
		shared<rend::ModelRenderer> GetModelRenderer() const;
	};
}