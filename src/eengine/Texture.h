#include "Resource.h"

#if EENGINE_USING_REND
#include <rend/Texture.h>
#endif // EENGINE_USING_REND

namespace eengine
{
	// Engine forward declarations
	class QuadRenderer;

	class Texture : public Resource 
	{
		friend class Resources;
		friend class QuadRenderer;
	private:
#if EENGINE_USING_REND
		shared<rend::Texture> m_rendTexture;

		/// @brief Get the rend representation of this Texture. Only available if Rend is being used.
		/// @return A shared pointer to the rend representation of this Texture.
		shared<rend::Texture> GetRendTexture();
#endif // EENGINE_USING_REND

		void Load();
	public:
	};
}