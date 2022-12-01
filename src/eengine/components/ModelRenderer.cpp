#include "ModelRenderer.h"

#include "../Core.h"
#include "../Resources.h"
#include "../RenderContext.h"
#include "../Entity.h"

#if EENGINE_USING_REND
#include <rend/rend.h>
#endif // EENGINE_USING_REND

namespace eengine 
{
	ModelRenderer::ModelRenderer() 
	{
	}

	ModelRenderer::ModelRenderer(const std::string& _modelPath) :
		m_modelPath(_modelPath)
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
#if EENGINE_USING_REND
		shared<rend::ModelRenderer> renderer = _renderContext->GetModelRenderer();
		renderer->Renderer::model(GetParent()->GetTransform()->GetModelMatrix());
		renderer->model(m_model->GetRendModel().get());
		renderer->shader(m_shader->GetRendShader().get());
		
		renderer->render();
#endif // EENGINE_USING_REND
	}
}