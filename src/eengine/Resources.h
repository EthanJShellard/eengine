#include <unordered_map>
#include <string>
#include <stdexcept>

#include "NonCopyable.h"
#include "eengine_defines.h"
#include "Debug.h"

namespace rend
{
	struct Shader;
	struct Texture;
	struct Model;
}


namespace eengine 
{
	class Core;
	class Resource;
	class Shader;

	/// @brief Class which governs the loading, storing and retrieval of engine resources.
	class Resources : public NonCopyable
	{
		friend class Core;

	private:
		Resources(std::string _projectWorkingDirectory);

		std::unordered_map<std::string, shared<Resource>> m_resources;

		// Project working directory.
		std::string m_pwd;
		weak<Resources> m_self;
	public:

		/// @brief Load a Shader resource.
		/// @param _vertPath The path to the vertex shader.
		/// @param _fragPath The path to the fragment shader.
		/// @return A shared pointer to the Shader resource.
		shared<Shader> LoadShader(std::string _vertPath, std::string _fragPath);

		/// @brief Load a Resource, or get it if it has already been loaded.
		/// @tparam T The type of the resource.
		/// @param _path The relative path to the Resource.
		/// @return A shared pointer to the Resource.
		template <typename T>
		shared<T> Load(std::string _path);

		/// @brief Unload a Resource, such that the engine will not hold onto it.
		/// @details The Resource's memory will only actually be released when there are no remaining strong references to the Resource. 
		/// It is recommended to only call this when you can make sure remaining strong references will go out of scope. 
		/// This is especially true if the Resource may be loaded again in future as you risk leaking memory otherwise.
		/// @param _path The path to the Resource.
		void Unload(std::string _path);
	};

	template <typename T>
	shared<T> Resources::Load(std::string _path)
	{
		// Check if Resource has already been loaded!
		auto itr = m_resources.find(_path);
		if (itr != m_resources.end())
		{
			auto castedPtr = std::dynamic_pointer_cast<T>(itr->second);
			if (!castedPtr) 
			{
				throw std::runtime_error("Attempted to load resource with valid path but invalid type!");
			}
			return castedPtr;
		}

		// Resource not found! Let's load it!
		shared<T> newResource = std::make_shared<T>();
		newResource->m_path = m_pwd + _path;
		newResource->m_resources = m_self;

		// Attempt to load
		try
		{
			newResource->OnCreate();
			newResource->Load();
			newResource->OnLoad();

			m_resources.insert(std::pair<std::string, shared<Resource>>(_path, newResource));

			return newResource;
		}
		catch (std::runtime_error e)
		{
			// Failed to load the resource!
			Debug::Log(e.what());

			return NULL;
		}
	}
}