#include "Model.h"


namespace eengine 
{
#if EENGINE_USING_REND
	shared<rend::Model> Model::GetRendModel() 
	{
		return m_rendModel;
	}
#endif // EENGINE_USING_REND

	void Model::Load() 
	{
#if EENGINE_USING_REND
		m_rendModel = std::make_shared<rend::Model>(m_path.c_str());
#endif // EENGINE_USING_REND
	}
}