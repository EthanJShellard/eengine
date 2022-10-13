#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main()
{
    std::cout << "Hello World" << std::endl;
    eengine::Core::TestFunction();

    shared<eengine::Core> core = eengine::Core::Initialise();
    auto e = core->AddEntity();
    
    e->Destroy();
    core->AddEntity()->AddComponent<Suicider>(5);

    core->Start();

    return 0;
}