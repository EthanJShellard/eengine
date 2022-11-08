#include "Shader.h"

namespace eengine 
{
	void Shader::Load() 
	{
#if EENGINE_USING_REND
		m_rendShader = std::make_shared<rend::Shader>(m_vertPath.c_str(), m_fragPath.c_str());
#endif // EENGINE_USING_REND
	}

#if EENGINE_USING_REND
	shared<rend::Shader> Shader::GetRendShader() 
	{
		return m_rendShader;
	}
#endif // EENGINE_USING_REND

	std::string Shader::GetFragPath() const
	{
		return m_fragPath;
	}

	std::string Shader::GetVertPath() const
	{
		return m_vertPath;
	}
}