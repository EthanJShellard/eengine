#include "../Core.h"
#include "../Environment.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Input.h"
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
		std::string pwd = GetCore()->GetEnvironment()->GetProjectWorkingDirectory();
		m_shader.LoadShaders((pwd + std::string("\\data\\shaders\\basic.vert")).c_str(), (pwd + std::string("\\data\\shaders\\basic.frag")).c_str());
	}

	void QuadRenderer::OnDisplay(shared<rend::Renderer> _renderer) 
	{
		_renderer->model(GetParent()->GetTransform()->GetModelMatrix());
		_renderer->shader(&m_shader);
		_renderer->mesh(&m_mesh);
		_renderer->color(m_colour);
				 
		_renderer->render();
	}

	void QuadRenderer::SetColour(float _r, float _g, float _b, float _a) 
	{
		m_colour = glm::vec4(_r,_g,_b,_a);
	}
}