#include "../Core.h"
#include "../Resources.h"
#include "../RenderContext.h"
#include "../Entity.h"
// Same as in QuadRenderer.cpp - for some reason ModelRenderer.h needs to be included after Core.h
#include "ModelRenderer.h"

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
			m_model = GetCore()->GetResources()->GetModel(m_modelPath);
		}

		// Default shader
		m_shader = GetCore()->GetResources()->GetShader("\\data\\shaders\\basic.vert", "\\data\\shaders\\basic.frag");
	}

	void ModelRenderer::SetModel(const std::string& _modelPath) 
	{
		m_modelPath = _modelPath;
		m_model = GetCore()->GetResources()->GetModel(m_modelPath);
	}

	void ModelRenderer::OnDisplay(shared<RenderContext> _renderContext) 
	{
		shared<rend::ModelRenderer> renderer = _renderContext->GetModelRenderer();
		renderer->Renderer::model(GetParent()->GetTransform()->GetModelMatrix());
		renderer->model(m_model.get());
		renderer->shader(m_shader.get());
		
		renderer->render();
	}
}