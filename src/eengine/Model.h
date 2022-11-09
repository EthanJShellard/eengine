#include "Resource.h"

#if EENGINE_USING_REND
#include <rend/Model.h>
#endif // EENGINE_USING_REND

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
#if EENGINE_USING_REND
		shared<rend::Model> m_rendModel;

		/// @brief Get the rend representation of this model. Only available when using rend.
		/// @return A shared pointer to the rend representation of this model.
		shared<rend::Model> GetRendModel();
#endif // EENGINE_USING_REND

		void Load();
	public:

	};
}