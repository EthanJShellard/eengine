#ifndef EENGINE_DEBUG
#define EENGINE_DEBUG

#include <string>
#include <glm/glm.hpp>

namespace eengine 
{
	/// @brief A class which collects the handling of debug information, visualisation and logging.
	class Debug 
	{
	public:
		/// @brief Print a string to the debug console.
		/// @param _str The string to print.
		static void Log(const char* _str);

		/// @brief Print a string to the debug console.
		/// @param str The string to print.
		static void Log(const std::string& _str);

		/// @brief Print a vector to the debug console.
		/// @param _vectorName The name of the vector.
		/// @param _vector The vector.
		static void Log(const std::string& _vectorName, const glm::vec3& _vector);
	};
}

#endif // EENGINE_DEBUG