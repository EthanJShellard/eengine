#include <string>

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
		static void Log(const std::string& str);
	};
}