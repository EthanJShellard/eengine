#include <iostream>

#include "Suicider.h"
#include "Entity.h"

Suicider::Suicider() 
{
	m_target = 10;
	m_count = 0;
}

Suicider::Suicider(int _target) 
{
	m_target = _target;
	m_count = 0;
}


void Suicider::OnTick() 
{
	if (m_count == m_target)
	{
		GetParent()->Destroy();
	}
	else 
	{
		m_count++;
		std::cout << "Hello!" << std::endl;
	}
}