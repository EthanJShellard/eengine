#include "Mesh.h"

namespace eengine 
{
	shared<rend::Mesh> Mesh::GetRendMesh() 
	{
		return m_rendMesh;
	}

	void Mesh::SetAsQuad() 
	{
		// Make sure destructor is called so old data is disposed of.
		m_rendMesh = std::make_shared<rend::Mesh>(rend::Mesh::QUAD);
	}

	void Mesh::Load() 
	{
		m_rendMesh = std::make_shared<rend::Mesh>(m_path.c_str());
	}
}