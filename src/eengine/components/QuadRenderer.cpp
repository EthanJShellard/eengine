#include "../Core.h"
#include "../Environment.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Input.h"
#include "../Resources.h"
#include "../RenderContext.h"
// For some reason QuadRenderer needs to be included after Core...... Query this....
#include "QuadRenderer.h"

namespace eengine 
{
	QuadRenderer::QuadRenderer() :
		m_mesh(),
		m_colour(glm::vec4(1.0f))
	{
		m_mesh.loadQuad();
	}

	void QuadRenderer::OnTick() 
	{
		auto transform = GetParent()->GetTransform();
		transform->Rotate(GetCore()->GetEnvironment()->GetDeltaTime() * 90.0f, transform->Up());

		if (GetCore()->GetInput()->GetKeyDown(KeyCode::minus)) 
		{
			transform->SetScale(transform->GetScale() * 0.95f);
		}

		if (GetCore()->GetInput()->GetKeyUp(KeyCode::equals))
		{
			transform->SetScale(transform->GetScale() * 1.05f);
		}
	}

	void QuadRenderer::OnInit() 
	{
		m_shader = GetCore()->GetResources()->GetShader("\\data\\shaders\\basic.vert", "\\data\\shaders\\basic.frag");
		m_texture = GetCore()->GetResources()->GetTexture("\\data\\textures\\dexter.jpg");
	}

	void QuadRenderer::OnDisplay(shared<RenderContext> _renderContext)
	{
		shared<rend::Renderer> renderer = _renderContext->GetMeshRenderer();
		renderer->model(GetParent()->GetTransform()->GetModelMatrix());
		renderer->shader(m_shader.get());
		renderer->mesh(&m_mesh);
		renderer->color(m_colour);
		renderer->texture(m_texture.get());
			 
		renderer->render();
	}

	void QuadRenderer::SetColour(float _r, float _g, float _b, float _a) 
	{
		m_colour = glm::vec4(_r,_g,_b,_a);
	}
}