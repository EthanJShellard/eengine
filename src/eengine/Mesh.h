#include "Resource.h"

#include <rend/Mesh.h>

namespace eengine 
{
	// eengine forward declarations
	class QuadRenderer;

	/// @brief eengine wrapper for Mesh resources.
	class Mesh : public Resource 
	{
		friend class QuadRenderer;
	private:
		shared<rend::Mesh> m_rendMesh;

		/// @brief Get the rend represenation of this Mesh. Only available when using rend.
		/// @return A shared pointer to the rend representation of this Mesh.
		shared<rend::Mesh> GetRendMesh();

		/// @brief Load the mesh from the Resource path.
		void Load();

	public:
		/// @brief Dispose of this mesh and replace it with a quad.
		void SetAsQuad();
	};
}