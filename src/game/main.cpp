#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main(int argc, char* argv[])
{
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);
    auto e = core->AddEntity();
    e->AddComponent<eengine::QuadRenderer>();
    e->m_transform->Translate(e->m_transform->Forward() * 5.0f);

    auto e2 = core->AddEntity();
    e2->AddComponent<eengine::QuadRenderer>();
    e2->m_transform->Translate(e->m_transform->Forward() * -5.0f);

    auto e3 = core->AddEntity();
    e3->AddComponent<eengine::QuadRenderer>();
    e3->m_transform->Translate(e->m_transform->Right() * 5.0f);

    auto e4 = core->AddEntity();
    e4->AddComponent<eengine::QuadRenderer>();
    e4->m_transform->Translate(e->m_transform->Right() * -5.0f);

   // core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}