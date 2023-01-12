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

		/// @brief Load model at the resource path if available and load basic shaders.
		void OnInit();

		/// @brief Set the model that this renderer should draw.
		/// @param _modelPath Path to the model that should be drawn by this renderer
		void SetModel(const std::string& _modelPath);

		/// @brief Set the tiling ratios this renderer will use.
		/// @param _ratioX The horizontal tiling ratio.
		/// @param _ratioY The vertical tiling ratio.
		void SetTilingRatios(float _ratioX, float _ratioY);

		/// @brief Get the current tiling ratios of this renderer.
		/// @return The current tiling ratios.
		glm::vec2 GetTilingRatios() const;

		/// @brief Set the alpha override that this renderer will use.
		/// @param _newAlpha The alpha value.
		void SetAlpha(float _newAlpha);

		/// @brief Get the current alpha override of this renderer.
		/// @return The alpha value.
		float GetAlpha() const;

		/// @brief Set the positional offset of this renderer.
		/// @param _offset The offset.
		void SetPosition(const glm::vec3& _offset);

		/// @brief Get the positional offset of thit renderer.
		/// @return The offset.
		glm::vec3 GetPosition() const;

		/// @brief Set the orientation offset of this renderer.
		/// @param _orientation The offset.
		void SetOrientation(const glm::quat& _orientation);

		/// @brief Get the orientation offset of this renderer.
		/// @return The offset.
		glm::quat GetOrientation() const;

		/// @brief Set the scale multiplier of this renderer.
		/// @param _scale The multiplier.
		void SetScale(const glm::vec3& _scale);

		/// @brief Get the scale multiplier of this renderer.
		/// @return The multiplier.
		glm::vec3 GetScale() const;
	};
}