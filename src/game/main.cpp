#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main()
{
    shared<eengine::Core> core = eengine::Core::Initialise();
    auto e = core->AddEntity();
    
    //e->AddComponent<eengine::QuadRenderer>();
    core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}