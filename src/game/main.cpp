#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main()
{
    shared<eengine::Core> core = eengine::Core::Initialise();
    auto e = core->AddEntity();
    
    e->Destroy();
    core->AddEntity()->AddComponent<Suicider>(10);

    core->Start();

    return 0;
}