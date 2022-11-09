#include "Resource.h"

#if EENGINE_USING_REND
#include <rend/Mesh.h>
#endif // EENGINE_USING_REND

namespace eengine 
{
	// eengine forward declarations
	class QuadRenderer;

	class Mesh : public Resource 
	{
		friend class QuadRenderer;
	private:
#if EENGINE_USING_REND
		shared<rend::Mesh> m_rendMesh;

		/// @brief Get the rend represenation of this Mesh. Only available when using rend.
		/// @return A shared pointer to the rend representation of this Mesh.
		shared<rend::Mesh> GetRendMesh();
#endif // EENGINE_USING_REND

		void Load();

	public:
		/// @brief Dispose of this mesh and replace it with a quad.
		void SetAsQuad();
	};
}