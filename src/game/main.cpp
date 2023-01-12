#include <iostream>

#include <eengine/eengine.h>
#include "components/PlayerController.h"
#include "components/WeaponPickup.h"
#include "components/DoorCrate.h"

shared<eengine::Entity> CreateWall(shared<eengine::Core> _core, const glm::vec3& _dimensions, const glm::vec2& _tilingMultiplier)
{
    auto wall = _core->AddEntity();
    wall->GetTransform()->SetScale(_dimensions.x, _dimensions.y, _dimensions.z);
    auto wall1Renderer = wall->AddComponent<eengine::ModelRenderer>("/data/models/brick_wall/wall.obj");
    wall1Renderer->SetTilingRatios(_tilingMultiplier.x * _dimensions.x, _tilingMultiplier.y * _dimensions.y);
    auto wall1rb = wall->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(_dimensions.x, _dimensions.y, _dimensions.z), 1.0f);
    wall1rb->SetIsStatic(true);
    return wall;
}

// doorPositions: North (-z), East (+x), South (+z) and West (-x)
void CreateRoom(shared<eengine::Core> _core, const glm::vec3& _centre, const glm::vec3& _dimensions, float _wallThickness, const glm::vec2& _wallTilingMultiplier, float _doorWidth, float _doorHeight, const glm::bvec4& _doorPositions) 
{
    float halfHeight = _dimensions.y / 2.0f;
    float halfThickness = _wallThickness / 2.0f;

    // North wall
    if (_doorPositions.x)
    {
        float wallLength = (_dimensions.x - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3((- wallLength - _doorWidth) / 2.0f, halfHeight, -_dimensions.z / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3((wallLength + _doorWidth) / 2.0f, halfHeight, -_dimensions.z / 2.0f));

        if (_doorHeight < _dimensions.y) 
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight , halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(0.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), -_dimensions.z / 2.0f));
        }
    }
    else
    {
        auto northWall = CreateWall(_core, glm::vec3(_dimensions.x, _dimensions.y, halfThickness), _wallTilingMultiplier);
        northWall->GetTransform()->Translate(_centre + glm::vec3(0.0f, halfHeight, -_dimensions.z / 2.0f));
    }

    // East wall
    if (_doorPositions.y)
    {
        float wallLength = (_dimensions.z - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, halfHeight, (-wallLength - _doorWidth) / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, halfHeight, (wallLength + _doorWidth) / 2.0f));
        leftWall->GetTransform()->Rotate(90.0f, glm::vec3(0,1,0));
        rightWall->GetTransform()->Rotate(90.0f, glm::vec3(0,1,0));

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), 0.0f));
            doorTopper->GetTransform()->Rotate(90.0f, glm::vec3(0,1,0));
        }
    }
    else
    {
        auto eastWall = CreateWall(_core, glm::vec3(_dimensions.z, _dimensions.y, halfThickness), _wallTilingMultiplier);
        eastWall->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, halfHeight, 0.0f));
        eastWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
    }

    // South Wall
    if (_doorPositions.z)
    {
        float wallLength = (_dimensions.x - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3((-wallLength - _doorWidth) / 2.0f, halfHeight, _dimensions.z / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3((wallLength + _doorWidth) / 2.0f, halfHeight, _dimensions.z / 2.0f));

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(0.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), _dimensions.z / 2.0f));
        }
    }
    else
    {
        auto southWall = CreateWall(_core, glm::vec3(_dimensions.x, _dimensions.y, halfThickness), _wallTilingMultiplier);
        southWall->GetTransform()->Translate(_centre + glm::vec3(0.0f, halfHeight, _dimensions.z / 2.0f));
    }

    // West wall
    if (_doorPositions.w)
    {
        float wallLength = (_dimensions.z - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, (-wallLength - _doorWidth) / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, (wallLength + _doorWidth) / 2.0f));
        leftWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        rightWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), 0.0f));
            doorTopper->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        }
    }
    else
    {
        auto eastWall = CreateWall(_core, glm::vec3(_dimensions.z, _dimensions.y, halfThickness), _wallTilingMultiplier);
        eastWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, 0.0f));
        eastWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
    }

    // Ceiling
    auto ceiling = _core->AddEntity();
    ceiling->AddComponent<eengine::ModelRenderer>("/data/models/ceiling/ceiling.obj")->SetTilingRatios(_dimensions.x / 5.0f, _dimensions.z / 5.0f);
    auto ceilingRb = ceiling->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(_dimensions.x, _wallThickness, _dimensions.z), 1.0f);
    ceilingRb->SetIsStatic(true);
    ceiling->GetTransform()->SetPosition(_centre + glm::vec3(0.0f, _dimensions.y + halfThickness, 0.0f));
    ceiling->GetTransform()->SetScale(_dimensions.x, _wallThickness, _dimensions.z);

}



int main(int argc, char* argv[])
{
 
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);

    {
        // Floor
        auto floor = core->AddEntity();
        floor->GetTransform()->Translate(glm::vec3(0.8f, -0.25f, -5.0f));
        floor->GetTransform()->SetScale(50.0f, 0.5, 50.0f);
        auto floorRenderer = floor->AddComponent<eengine::ModelRenderer>("/data/models/concrete_floor/floor.obj");
        floorRenderer->SetTilingRatios(50, 50);
        auto rb = floor->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(100.0f, 0.5f, 100.0f), 1.0f);
        rb->SetFriction(1.5f);
        rb->SetIsStatic(true);

        // Starting room
        CreateRoom(core, glm::vec3(0,0,0), glm::vec3(10.0f, 3.0f, 10.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(true, true, false, false));

        // Weapon room
        CreateRoom(core, glm::vec3(0,0,-10.0f), glm::vec3(10.0f, 2.0f, 10.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(false, false, true, false));
        auto weaponPickup = core->AddEntity();
        weaponPickup->AddComponent<eengine::ModelRenderer>("/data/models/tank/IS4.obj");
        auto pickupTrans = weaponPickup->GetTransform();
        pickupTrans->SetPosition(0.0f,0.5f,-10.0f);
        pickupTrans->SetScale(glm::vec3(0.2f));
        auto pickupRB = weaponPickup->AddComponent<eengine::RigidBody>(std::make_shared<eengine::SphereCollider>(0.2f), 1.0f);
        pickupRB->SetIsTrigger(true);
        weaponPickup->AddComponent<WeaponPickup>(0.3f, 45.0f, 45.0f);
        auto pickupAS = weaponPickup->AddComponent<eengine::AudioSource>();
        auto pickupVoice = core->GetResources()->Load<eengine::Sound>("/data/audio/tank/voice.ogg");
        pickupVoice->SetDirectional(true);
        pickupAS->SetLooping(true);
        pickupAS->SetVolume(2.0f);
        pickupAS->PlayOneShot(pickupVoice);

        // Preload explosion model
        core->GetResources()->Load<eengine::Model>("/data/models/explosion/explosion.obj");

        // Combat room
        CreateRoom(core, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(20.0f, 15.0f, 30.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(false, true, false, true));
        auto combatRoomSplitter1 = core->AddEntity();

        // Room divider
        combatRoomSplitter1->AddComponent<eengine::ModelRenderer>("/data/models/concrete_floor/floor.obj")->SetTilingRatios(30.0f, 7.5f);
        auto splitter1RB = combatRoomSplitter1->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(1.0f, 7.5f, 30.0f), 1.0f);
        splitter1RB->SetIsStatic(true);
        combatRoomSplitter1->GetTransform()->Translate(glm::vec3(15.0f, 0.0f, 0.0f));
        combatRoomSplitter1->GetTransform()->SetScale(1.0f, 7.5f, 30.0f);

        // Door blocking crate
        auto doorCrate = core->AddEntity();
        doorCrate->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(2.0f, 2.0f, 2.0f), 2.0f)->SetIsStatic(true);
        doorCrate->AddComponent<eengine::ModelRenderer>("/data/models/crate/crate1.obj");
        doorCrate->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
        doorCrate->GetTransform()->Translate(glm::vec3(6.0f, 1.0f, 0.0f));
        doorCrate->AddComponent<DoorCrate>();

        // Player
        auto player = core->AddEntity();
        auto playerRB = player->AddComponent<eengine::RigidBody>(std::make_shared<eengine::CapsuleCollider>(0.2f, 0.6f), 1.0f);
        playerRB->SetPositionAxesLocked(false, false, false);
        playerRB->SetRotationAxesLocked(true, true, true);
        playerRB->SetFriction(3.0f);
        player->AddComponent<PlayerController>();
        player->AddComponent<eengine::AudioListener>();
        player->AddComponent<eengine::AudioSource>();


        // Preload music
        auto musicPreload = core->GetResources()->Load<eengine::Sound>("/data/audio/music/e1m1.ogg");
        musicPreload->SetDirectional(false);
        musicPreload->GetID();

        // Set up input
        core->GetInput()->SetRelativeMouseMode(true);
        core->GetInput()->SetInputGrab(true);
    }

    core->Start();

    return 0;
}