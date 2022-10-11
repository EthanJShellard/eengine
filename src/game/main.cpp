#include <iostream>
#include "eengine.h"

int main()
{
    std::cout << "Hello World" << std::endl;
    eengine::Core::TestFunction();

    shared<eengine::Core> core = eengine::Core::Initialise();
    auto e = core->AddEntity();
    auto e2 = core->AddEntity();
    
    e->Destroy();
    e2->Destroy();

    core->Start();

    return 0;
}