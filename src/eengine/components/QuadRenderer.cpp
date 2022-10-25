#include "../Core.h"
#include "../Environment.h"
#include "../Entity.h"
// For some reason QuadRenderer needs to be included after Core...... Query this....
#include "QuadRenderer.h"

namespace eengine 
{
	QuadRenderer::QuadRenderer() :
		m_mesh()
	{
		m_mesh.loadQuad();
	}

	void QuadRenderer::OnInitialise() 
	{
		std::string pwd = GetCore()->GetEnvironment()->GetProjectWorkingDirectory();
		m_shader.LoadShaders((pwd + std::string("\\data\\shaders\\basic.vert")).c_str(), (pwd + std::string("\\data\\shaders\\basic.frag")).c_str());
	}

	void QuadRenderer::OnDisplay() 
	{
		rend::Renderer r(640, 480);

		r.model(GetParent()->m_transform->GetModelMatrix());
		r.shader(&m_shader);
		r.mesh(&m_mesh);

		r.render();
	}
}