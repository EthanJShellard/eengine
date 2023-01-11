#include "Shader.h"

namespace eengine 
{
	void Shader::Load() 
	{
		m_rendShader = std::make_shared<rend::Shader>(m_vertPath.c_str(), m_fragPath.c_str());
	}

	shared<rend::Shader> Shader::GetRendShader() 
	{
		return m_rendShader;
	}

	std::string Shader::GetFragPath() const
	{
		return m_fragPath;
	}

	std::string Shader::GetVertPath() const
	{
		return m_vertPath;
	}
}