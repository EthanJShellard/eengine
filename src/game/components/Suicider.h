#include "eengine.h"

COMPONENT(Suicider)
{
public:
	Suicider();
	Suicider(int _target);

private:
	void OnTick() override;

	int m_count;
	int m_target;
};