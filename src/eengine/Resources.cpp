#include <rend/Shader.h>

#include "Resources.h"
#include "Core.h"
#include "Environment.h"

namespace eengine 
{
	Resources::Resources(std::string _projectWorkingDirectory) :
		m_pwd(_projectWorkingDirectory)
	{
	}

	shared<rend::Shader> Resources::GetShader(std::string _fragLocation, std::string _vertLocation)
	{
		// Check if shader has already been loaded!
		auto locs = _fragLocation + _vertLocation;
		auto itr = m_shaders.find(locs);
		if (itr != m_shaders.end()) 
		{
			return itr->second;
		}

		// Shader not found! Lets create it!
		shared<rend::Shader> newShader = std::make_shared<rend::Shader>();
		newShader->LoadShaders((m_pwd + _fragLocation).c_str(), (m_pwd + _vertLocation).c_str());
		m_shaders.insert(std::pair< std::string, shared<rend::Shader > >(locs, newShader));
		return newShader;
	}
}