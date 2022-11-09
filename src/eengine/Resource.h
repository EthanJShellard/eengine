#ifndef EENGINE_RESOURCE
#define EENGINE_RESOURCE

#include <string>

#include "eengine_defines.h"
#include "NonCopyable.h"

namespace eengine 
{
	// Engine forward declarations
	class Resources;

	/// @brief Superclass for eengine resources. In most cases, resources should be obtained via Resources.
	class Resource : public NonCopyable
	{
		friend class Resources;
	private:
		/// @brief Attempt to read and load the resource's data from the provided path.
		virtual void Load();

	protected:
		std::string m_path;
		weak<Resources> m_resources;
		
	public:
		/// @brief Called immediately after Load().
		virtual void OnLoad();

		/// @brief Called immediately before Load().
		virtual void OnCreate();

		/// @brief Get the relative path to this resource.
		/// @return A string representing the relative path to this resource.
		std::string GetPath() const;
	};
}

#endif // EENGINE_RESOURCE