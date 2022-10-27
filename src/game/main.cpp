#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"

int main(int argc, char* argv[])
{
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);
    auto e = core->AddEntity();
    e->AddComponent<eengine::QuadRenderer>()->SetColour(1.0f,0.0f,0.0f,0.5f);
    e->GetTransform()->Translate(glm::vec3(0.8f, 0.0f, -5.0f));

    auto e2 = core->AddEntity();
    e2->AddComponent<eengine::QuadRenderer>()->SetColour(0.0f, 1.0f, 0.0f, 0.5f);;
    e2->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -5.0f));

    auto e3 = core->AddEntity();
    e3->AddComponent<eengine::QuadRenderer>()->SetColour(0.0f, 0.0f, 1.0f, 0.5f);
    e3->AddComponent<eengine::QuadRenderer>()->SetColour(0.9f, 0.9f, 0.9f, 0.4f);;
    e3->GetTransform()->Translate(glm::vec3(-0.8f, 0.0f, -5.0f));
    // Test getting component by type
    e3->GetComponentOfType<eengine::QuadRenderer>()->SetColour(1.0f,0,1.0f,0.8f);
    // Test getting multiple components
    int size = e3->GetComponentsOfType<eengine::QuadRenderer>().size();

   // core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}