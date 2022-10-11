#include "Component.h"

class Suicider : public eengine::Component 
{
	void OnTick() override;

	int count = 0;
};