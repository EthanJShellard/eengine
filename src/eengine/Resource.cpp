#include "Resource.h"

namespace eengine 
{
	std::string Resource::GetPath() const 
	{
		return m_path;
	}

	void Resource::Load() {}
	void Resource::OnCreate() {}
	void Resource::OnLoad() {}
}