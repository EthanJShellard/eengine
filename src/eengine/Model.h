#include "Resource.h"

#include <rend/Model.h>

namespace eengine 
{
	// Engine forward declarations
	class ModelRenderer;

	/// @brief eengine wrapper for Model resources.
	class Model : public Resource 
	{
		friend class Resources;
		friend class ModelRenderer;
	private:
		shared<rend::Model> m_rendModel;

		/// @brief Get the rend representation of this model. Only available when using rend.
		/// @return A shared pointer to the rend representation of this model.
		shared<rend::Model> GetRendModel();

		void Load();
	};
}