#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main()
{
    std::cout << "Hello World" << std::endl;
    eengine::Core::TestFunction();

    shared<eengine::Core> core = eengine::Core::Initialise();
    auto e = core->AddEntity();
    auto e2 = core->AddEntity();
    
    e->Destroy();
    e2->AddComponent<Suicider>();

    core->Start();

    return 0;
}
// Ask if it is acceptable to ditch header guards