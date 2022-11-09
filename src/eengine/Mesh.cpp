#include "Mesh.h"

namespace eengine 
{
#if EENGINE_USING_REND
	shared<rend::Mesh> Mesh::GetRendMesh() 
	{
		return m_rendMesh;
	}
#endif // EENGINE_USING_REND

	void Mesh::SetAsQuad() 
	{
#if EENGINE_USING_REND
		// Make sure destructor is called so old data is disposed of.
		m_rendMesh = std::make_shared<rend::Mesh>(rend::Mesh::QUAD);
#endif // EENGINE_USING_REND
	}

	void Mesh::Load() 
	{
#if EENGINE_USING_REND
		m_rendMesh = std::make_shared<rend::Mesh>(m_path.c_str());
#endif // EENGINE_USING_REND
	}
}