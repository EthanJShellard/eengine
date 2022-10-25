#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main(int argc, char* argv[])
{
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);
    auto e = core->AddEntity();
    
    e->AddComponent<eengine::QuadRenderer>();
    core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}