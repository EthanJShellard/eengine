#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main(int argc, char* argv[])
{
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);
    auto e = core->AddEntity();
    e->AddComponent<eengine::QuadRenderer>();
    e->m_transform->Translate(glm::vec3(1, 0,-5.0f));

    auto e2 = core->AddEntity();
    e2->AddComponent<eengine::QuadRenderer>();
    e2->m_transform->Translate(glm::vec3(0,0,-5.0f));

    auto e3 = core->AddEntity();
    e3->AddComponent<eengine::QuadRenderer>();
    e3->m_transform->Translate(glm::vec3(-1,0,-5.0f));

   // core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}