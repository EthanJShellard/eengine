#include "QuadRenderer.h"
#include "../Mesh.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../Material.h"
#include "../Shader.h"

namespace eengine 
{
	QuadRenderer::QuadRenderer() 
	{
		m_mesh = std::make_shared<Mesh>();
		shared<VertexBuffer> vbo = std::make_shared<VertexBuffer>();
		vbo->Add(glm::vec3(0.0f, 0.0f, 0.0f));
		vbo->Add(glm::vec3(1.0f, 0.0f, 0.0f));
		vbo->Add(glm::vec3(1.0f, 1.0f, 0.0f));
		vbo->Add(glm::vec3(1.0f, 1.0f, 0.0f));
		vbo->Add(glm::vec3(0.0f, 1.0f, 0.0f));
		vbo->Add(glm::vec3(0.0f, 0.0f, 0.0f));
		m_mesh->m_vao->SetBuffer(vbo, 0);

		m_shader = std::make_shared<Shader>("shaders/fullbright_texture.vert", "shaders/fullbright_texture.frag");
		m_mesh->m_material->SetShader(m_shader);
	}

	void QuadRenderer::OnDisplay() 
	{
		
	}
}