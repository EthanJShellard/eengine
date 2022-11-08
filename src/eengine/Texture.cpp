#include "Texture.h"


namespace eengine
{
#if EENGINE_USING_REND
	shared<rend::Texture> Texture::GetRendTexture()
	{
		return m_rendTexture;
	}
#endif // EENGINE_USING_REND

	void Texture::Load() 
	{
#if EENGINE_USING_REND
		m_rendTexture = std::make_shared<rend::Texture>(m_path.c_str());
#endif // EENGINE_USING_REND
	}
}