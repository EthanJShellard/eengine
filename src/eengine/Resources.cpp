#include <rend/Shader.h>
#include <rend/Texture.h>
#include <rend/Model.h>

#include "Resources.h"
#include "Core.h"
#include "Environment.h"
#include "Resource.h"
#include "Debug.h"
#include "Shader.h"

namespace eengine 
{
	Resources::Resources(std::string _projectWorkingDirectory) :
		m_pwd(_projectWorkingDirectory)
	{
	}

	shared<Shader> Resources::LoadShader(std::string _vertPath, std::string _fragPath) 
	{
		// Create combined path
		std::string comboPath = _vertPath + _fragPath;

		// Check if Shader has already been loaded!
		auto itr = m_resources.find(comboPath);
		if (itr != m_resources.end())
		{
			// Will return null if you've somehow tried to load an existing non-shader resource using this function
			return std::dynamic_pointer_cast<Shader>(itr->second);
		}

		// Resource not found! Let's load it!
		shared<Shader> newShader = std::make_shared<Shader>();
		newShader->m_path = comboPath;
		newShader->m_resources = m_self;
		newShader->m_vertPath = m_pwd + _vertPath;
		newShader->m_fragPath = m_pwd + _fragPath;

		// Attempt to load
		try
		{
			newShader->OnCreate();
			newShader->Load();
			newShader->OnLoad();

			m_resources.insert(std::pair<std::string, shared<Resource>>(comboPath, newShader));

			return newShader;
		}
		catch (std::runtime_error e)
		{
			// Failed to load the resource!
			Debug::Log(e.what());

			return NULL;
		}
	}
}