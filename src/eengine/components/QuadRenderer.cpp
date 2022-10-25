#include "QuadRenderer.h"

namespace eengine 
{
	QuadRenderer::QuadRenderer() :
		m_shader("data/shaders/basic.vert", "data/shaders/basic.frag"),
		m_mesh()
	{
		m_mesh.loadQuad();
	}

	void QuadRenderer::OnDisplay() 
	{
		rend::Renderer r(640, 480);

		r.shader(&m_shader);
		r.mesh(&m_mesh);

		r.render();
	}
}