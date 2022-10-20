#include <GL/glew.h>
#include <glm/ext.hpp>

#include "Material.h"
#include "Shader.h"
#include "Texture.h"

namespace eengine 
{
	void Material::SetShader(shared<Shader> _newShader)
	{
		m_shader = _newShader;

		// Store location of available uniforms
		m_textureLocation = glGetUniformLocation(m_shader->GetID(), "u_Texture");
		m_modelMatLocation = glGetUniformLocation(m_shader->GetID(), "u_Model");
		m_projMatLocation = glGetUniformLocation(m_shader->GetID(), "u_Projection");
		m_viewMatLocation = glGetUniformLocation(m_shader->GetID(), "u_View");
	}

	

	void Material::Apply(glm::mat4 _model, glm::mat4 _projection, glm::mat4 _iView, glm::vec3 _camPos)
	{
		//Bind shader program
		glUseProgram(m_shader->GetID());
		//Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->m_id);

		//Upload matrices
		glUniformMatrix4fv(m_modelMatLocation, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(m_projMatLocation, 1, GL_FALSE, glm::value_ptr(_projection));
		glUniformMatrix4fv(m_viewMatLocation, 1, GL_FALSE, glm::value_ptr(_iView));

		//Upload camera position
		glUniform3f(m_camPositionLocation, _camPos.x, _camPos.y, _camPos.z);
	}

	Material::Material()
	{
		m_modelMatLocation = 0;
		m_viewMatLocation = 0;
		m_projMatLocation = 0;
		m_textureLocation = 0;
		m_camPositionLocation = 0;
	}
}