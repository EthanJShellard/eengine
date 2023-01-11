#include "Resource.h"

#include <rend/Texture.h>

namespace eengine
{
	// Engine forward declarations
	class QuadRenderer;

	/// @brief eengine wrapper for Texture resources.
	class Texture : public Resource 
	{
		friend class Resources;
		friend class QuadRenderer;
	private:
		shared<rend::Texture> m_rendTexture;

		/// @brief Get the rend representation of this Texture. Only available if Rend is being used.
		/// @return A shared pointer to the rend representation of this Texture.
		shared<rend::Texture> GetRendTexture();

		void Load();
	public:
	};
}