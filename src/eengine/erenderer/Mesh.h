#include "../eengine_defines.h"

namespace eengine 
{
	// Engine forward declarations
	class VertexArray;
	class Material;

	class Mesh 
	{
	public:
		shared<VertexArray> m_vao;
		shared<Material> m_material;
	};
}