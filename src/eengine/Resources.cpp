#include <rend/Shader.h>
#include <rend/Texture.h>

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

		// Shader not found! Let's create it!
		shared<rend::Shader> newShader = std::make_shared<rend::Shader>((m_pwd + _fragLocation).c_str(), (m_pwd + _vertLocation).c_str());
		m_shaders.insert(std::pair< std::string, shared<rend::Shader > >(locs, newShader));
		return newShader;
	}

	shared<rend::Texture> Resources::GetTexture(std::string _texLocation) 
	{
		// Check if texture has already been loaded!
		auto itr = m_textures.find(_texLocation);
		if (itr != m_textures.end()) 
		{
			return itr->second;
		}

		// Texture not found! Let's create it!
		shared<rend::Texture> newTexture = std::make_shared<rend::Texture>((m_pwd + _texLocation).c_str());
		m_textures.insert(std::pair<std::string, shared<rend::Texture>>(_texLocation, newTexture));
		return newTexture;
	}
}