#include "ModelRenderer.h"

#include "../Core.h"
#include "../Resources.h"
#include "../RenderContext.h"
#include "../Entity.h"

#include <rend/rend.h>

namespace eengine 
{
	ModelRenderer::ModelRenderer() :
		m_tilingRatios(1.0f),
		m_alpha(1.0f)
	{
	}

	ModelRenderer::ModelRenderer(const std::string& _modelPath) :
		m_modelPath(_modelPath),
		m_tilingRatios(1.0f),
		m_alpha(1.0f)
	{
	}

	void ModelRenderer::OnInit() 
	{
		if (!m_modelPath.empty()) 
		{
			m_model = GetCore()->GetResources()->Load<Model>(m_modelPath);
		}

		// Default shader
		m_shader = GetCore()->GetResources()->LoadShader("/data/shaders/basic.vert", "/data/shaders/basic.frag");
	}

	void ModelRenderer::SetModel(const std::string& _modelPath) 
	{
		m_modelPath = _modelPath;
		m_model = GetCore()->GetResources()->Load<Model>(m_modelPath);
	}

	void ModelRenderer::OnDisplay(shared<RenderContext> _renderContext) 
	{
		shared<rend::ModelRenderer> renderer = _renderContext->GetModelRenderer();
		renderer->Renderer::model(GetParent()->GetTransform()->GetModelMatrix() * m_localTransform.GetModelMatrix());
		renderer->model(m_model->GetRendModel().get());
		renderer->shader(m_shader->GetRendShader().get());
		renderer->tilingRatio(m_tilingRatios);
		renderer->alpha(m_alpha);
		
		renderer->render();

		renderer->alpha(1.0f);
	}

	void ModelRenderer::SetTilingRatios(float _ratioX, float _ratioY)
	{
		m_tilingRatios = glm::vec2(_ratioX, _ratioY);
	}

	glm::vec2 ModelRenderer::GetTilingRatios() const
	{
		return m_tilingRatios;
	}

	void ModelRenderer::SetAlpha(float _newAlpha) 
	{
		m_alpha = _newAlpha;
	}

	float ModelRenderer::GetAlpha() const
	{
		return m_alpha;
	}

	void ModelRenderer::SetPosition(const glm::vec3& _offset) 
	{
		m_localTransform.SetPosition(_offset);
	}

	glm::vec3 ModelRenderer::GetPosition() const
	{
		return m_localTransform.GetPosition();
	}

	void ModelRenderer::SetOrientation(const glm::quat& _orientation) 
	{
		m_localTransform.SetRotation(_orientation);
	}

	glm::quat ModelRenderer::GetOrientation() const
	{
		return m_localTransform.GetQuaternionRotation();
	}

	void ModelRenderer::SetScale(const glm::vec3& _scale) 
	{
		m_localTransform.SetScale(_scale);
	}
	
	glm::vec3 ModelRenderer::GetScale() const
	{
		return m_localTransform.GetScale();
	}
}