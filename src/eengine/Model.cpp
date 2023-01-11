#include "Model.h"


namespace eengine 
{
	shared<rend::Model> Model::GetRendModel() 
	{
		return m_rendModel;
	}

	void Model::Load() 
	{
		m_rendModel = std::make_shared<rend::Model>(m_path.c_str());
	}
}