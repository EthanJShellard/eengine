#include <iostream>

#include <eengine/eengine.h>
#include "components/Suicider.h"
#include "components/ScreamingMover.h"
#include "components/PlayerController.h"

int main(int argc, char* argv[])
{
 
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);

    {
        auto e = core->AddEntity();
        e->AddComponent<eengine::QuadRenderer>()->SetColour(1.0f, 0.0f, 0.0f, 0.5f);
        e->GetTransform()->Translate(glm::vec3(0.8f, 0.0f, -5.0f));
        e->AddComponent<eengine::AudioSource>();
        //e->AddComponent<ScreamingMover>();
        

        auto e2 = core->AddEntity();
        e2->GetTransform()->Translate(glm::vec3(0.8f, -1.0f, -5.0f));
        e2->GetTransform()->SetScale(50.0f, 0.5, 50.0f);
        e2->AddComponent<eengine::ModelRenderer>("/data/models/Crate/UnitCube.obj");
        auto rb = e2->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(50.0f, 0.5f, 50.0f), 1.0f);
        rb->SetFriction(1.5f);
        rb->SetPositionAxesLocked(true, true, true);
        rb->SetRotationAxesLocked(true, true, true);

        auto e3 = core->AddEntity();
        e3->AddComponent<eengine::ModelRenderer>("/data/models/Crate/UnitCube.obj");
        e3->GetTransform()->Translate(glm::vec3(-1.0f, 0.0f, -5.0f));
        e3->GetTransform()->Scale(glm::vec3(0.3f, 0.3f, 0.3f));
        e3->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(0.25f, 0.25f, 0.25f), 1.0f);
        e3->AddComponent<Suicider>();

        auto player = core->AddEntity();
        auto playerRB = player->AddComponent<eengine::RigidBody>(std::make_shared<eengine::CylinderCollider>(0.5f, 0.5f, 0.5f), 1.0f);
        playerRB->SetPositionAxesLocked(false, false, false);
        playerRB->SetRotationAxesLocked(true, true, true);
        playerRB->SetFriction(3.0f);
        player->AddComponent<PlayerController>();
        player->AddComponent<eengine::AudioListener>();

        core->GetInput()->SetRelativeMouseMode(true);
        core->GetInput()->SetInputGrab(true);
    }
    

    //core->AddEntity()->AddComponent<Suicider>(30);

    core->Start();

    return 0;
}