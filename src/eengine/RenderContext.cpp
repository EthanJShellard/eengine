#include <SDL2/SDL.h>


#include "RenderContext.h"

namespace eengine 
{
	RenderContext::RenderContext()
	{
	}

	void RenderContext::Initialise(int _renderWidth, int _renderHeight) 
	{
		// Set up mesh renderer
		m_meshRenderer = std::make_shared<rend::Renderer>(_renderWidth, _renderHeight);
		m_meshRenderer->projection(glm::perspective(glm::radians(45.0f), (float)_renderWidth / (float)_renderHeight, 0.1f, 100.f));
		m_meshRenderer->backfaceCull(true);
		m_meshRenderer->blend(true);
		m_meshRenderer->depthTest(true);
		// Set up model renderer
		m_modelRenderer = std::make_shared<rend::ModelRenderer>(_renderWidth, _renderHeight);
		m_modelRenderer->projection(glm::perspective(glm::radians(45.0f), (float)_renderWidth / (float)_renderHeight, 0.1f, 100.f));
		m_modelRenderer->backfaceCull(true);
		m_modelRenderer->blend(true);
		m_modelRenderer->depthTest(true);
	}

	void RenderContext::SetMainViewMatrix(const glm::mat4& _newViewMatrix) 
	{
		// For now all renderers will use the main view matrix so will update all
		m_mainViewMatrix = _newViewMatrix;
		m_meshRenderer->view(m_mainViewMatrix);
		m_modelRenderer->view(m_mainViewMatrix);
	}

	void RenderContext::ClearAll() 
	{
		m_meshRenderer->clear();
		m_modelRenderer->clear();
	}

	RenderContext::~RenderContext() 
	{
		// Clean up rendering context and libraries where necessary.
		SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	}

	shared<rend::Renderer> RenderContext::GetMeshRenderer() const
	{
		return m_meshRenderer;
	}

	shared<rend::ModelRenderer> RenderContext::GetModelRenderer() const
	{
		return m_modelRenderer;
	}
}