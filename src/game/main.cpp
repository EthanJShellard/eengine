#include <iostream>

#include "eengine.h"
#include "components/Suicider.h"
#include "components/ScreamingMover.h"

int main(int argc, char* argv[])
{
 
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);

    {
        auto e = core->AddEntity();
        e->AddComponent<eengine::QuadRenderer>()->SetColour(1.0f, 0.0f, 0.0f, 0.5f);
        e->GetTransform()->Translate(glm::vec3(0.8f, 0.0f, -5.0f));
        e->AddComponent<eengine::AudioSource>();
        e->AddComponent<ScreamingMover>();
        

        auto e2 = core->AddEntity();
        e2->AddComponent<eengine::QuadRenderer>()->SetColour(0.0f, 1.0f, 0.0f, 0.5f);;
        e2->GetTransform()->Translate(glm::vec3(0.8f, -1.0f, -5.0f));
        auto rb = e2->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(50.0f, 0.5f, 50.0f), 1.0f);
        rb->SetYPosLocked(true);
        rb->SetXPosLocked(true);
        rb->SetZPosLocked(true);
        rb->SetXRotLocked(true);
        rb->SetYRotLocked(true);
        rb->SetZRotLocked(true);

        auto e3 = core->AddEntity();
        e3->AddComponent<eengine::ModelRenderer>("\\data\\models\\curuthers\\curuthers.obj");
        e3->GetTransform()->Translate(glm::vec3(-1.0f, 0.0f, -5.0f));
        e3->GetTransform()->Scale(glm::vec3(0.3f, 0.3f, 0.3f));
        e3->AddComponent<eengine::RigidBody>(std::make_shared<eengine::CylinderCollider>(0.5f, 0.5f, 0.5f), 1.0f);
        e3->AddComponent<Suicider>();
    }
    

    //core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}