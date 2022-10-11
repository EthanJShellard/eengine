#include <iostream>

#include "Suicider.h"
#include "Entity.h"

void Suicider::OnTick() 
{
	if (count == 10)
	{
		GetParent()->Destroy();
	}
	else 
	{
		count++;
		std::cout << "Hello!" << std::endl;
	}
}