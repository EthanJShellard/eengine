#include "Texture.h"


namespace eengine
{
	shared<rend::Texture> Texture::GetRendTexture()
	{
		return m_rendTexture;
	}

	void Texture::Load() 
	{
		m_rendTexture = std::make_shared<rend::Texture>(m_path.c_str());
	}
}