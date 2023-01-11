#include "../Component.h"
#include "../eengine_defines.h"
#include "../Model.h"
#include "../Shader.h"
#include "Transform.h"

namespace eengine 
{

	/// @brief A component which will render a rend::Model.
	class ModelRenderer : public Component
	{
	private:
		shared<Model> m_model;
		shared<Shader> m_shader;
		std::string m_modelPath;
		glm::vec2 m_tilingRatios;
		Transform m_localTransform;
		float m_alpha;
		
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

		void SetTilingRatios(float _ratioX, float _ratioY);
		glm::vec2 GetTilingRatios();

		void SetAlpha(float _newAlpha);
		float GetAlpha();

		void SetOffset(const glm::vec3& _offset);
		glm::vec3 GetOffset() const;

		void SetOrientation(const glm::quat& _orientation);
		glm::quat GetOrientation() const;

		void SetScale(const glm::vec3& _scale);
		glm::vec3 GetScale() const;
	};
}