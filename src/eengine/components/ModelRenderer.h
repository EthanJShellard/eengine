#include <rend/rend.h>

#include "../Component.h"
#include "../eengine_defines.h"

namespace eengine 
{
	/// @brief A component which will render a rend::Model.
	COMPONENT(ModelRenderer)
	{
	private:
		shared<rend::Model> m_model;
		shared<rend::Shader> m_shader;
		std::string m_modelPath;
		
		void OnDisplay(shared<RenderContext> _renderContext);
	public:
		
		ModelRenderer();

		/// @brief Construct a ModelRenderer such that it will load the model at _modelPath when initialised
		/// @param _modelPath Path to the model this renderer should draw.
		ModelRenderer(const std::string& _modelPath);

		void OnInit();

		/// @brief Set the model that this renderer should draw.
		/// @param _modelPath Path to the model that should be drawn by this renderer
		void SetModel(const std::string& _modelPath);
	};
}