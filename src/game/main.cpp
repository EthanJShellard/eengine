#include <iostream>

#include <eengine/eengine.h>
#include "components/Suicider.h"
#include "components/ScreamingMover.h"
#include "components/PlayerController.h"
#include "components/WeaponPickup.h"

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

/// @brief 
/// @param _core 
/// @param centre 
/// @param _dimensions 
/// @param _wallTilingMultiplier 
/// @param doorWidth 
/// @param doorPositions North (-z), East (+x), South (+z) and West (-x)
/// @return 
std::vector<shared<eengine::Entity>> CreateRoom(shared<eengine::Core> _core, const glm::vec3& _centre, const glm::vec3& _dimensions, float _wallThickness, const glm::vec2& _wallTilingMultiplier, float _doorWidth, float _doorHeight, const glm::bvec4& _doorPositions) 
{
    std::vector<shared<eengine::Entity>> walls;
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
        walls.push_back(leftWall);
        walls.push_back(rightWall);

        if (_doorHeight < _dimensions.y) 
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight , halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(0.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), -_dimensions.z / 2.0f));
            walls.push_back(doorTopper);
        }
    }
    else
    {
        auto northWall = CreateWall(_core, glm::vec3(_dimensions.x, _dimensions.y, halfThickness), _wallTilingMultiplier);
        northWall->GetTransform()->Translate(_centre + glm::vec3(0.0f, halfHeight, -_dimensions.z / 2.0f));
        walls.push_back(northWall);
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
        walls.push_back(leftWall);
        walls.push_back(rightWall);

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), 0.0f));
            doorTopper->GetTransform()->Rotate(90.0f, glm::vec3(0,1,0));
            walls.push_back(doorTopper);
        }
    }
    else
    {
        auto eastWall = CreateWall(_core, glm::vec3(_dimensions.z, _dimensions.y, halfThickness), _wallTilingMultiplier);
        eastWall->GetTransform()->Translate(_centre + glm::vec3(_dimensions.x / 2.0f, halfHeight, 0.0f));
        eastWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        walls.push_back(eastWall);
    }

    // South Wall
    if (_doorPositions.z)
    {
        float wallLength = (_dimensions.x - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3((-wallLength - _doorWidth) / 2.0f, halfHeight, _dimensions.z / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3((wallLength + _doorWidth) / 2.0f, halfHeight, _dimensions.z / 2.0f));
        walls.push_back(leftWall);
        walls.push_back(rightWall);

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(0.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), _dimensions.z / 2.0f));
            walls.push_back(doorTopper);
        }
    }
    else
    {
        auto southWall = CreateWall(_core, glm::vec3(_dimensions.x, _dimensions.y, halfThickness), _wallTilingMultiplier);
        southWall->GetTransform()->Translate(_centre + glm::vec3(0.0f, halfHeight, _dimensions.z / 2.0f));
        walls.push_back(southWall);
    }

    // West wall
    if (_doorPositions.y)
    {
        float wallLength = (_dimensions.z - _doorWidth) / 2.0f;
        auto leftWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        auto rightWall = CreateWall(_core, glm::vec3(wallLength, _dimensions.y, halfThickness), _wallTilingMultiplier);
        leftWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, (-wallLength - _doorWidth) / 2.0f));
        rightWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, (wallLength + _doorWidth) / 2.0f));
        leftWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        rightWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        walls.push_back(leftWall);
        walls.push_back(rightWall);

        if (_doorHeight < _dimensions.y)
        {
            auto doorTopper = CreateWall(_core, glm::vec3(_doorWidth, _dimensions.y - _doorHeight, halfThickness), _wallTilingMultiplier);
            doorTopper->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, _doorHeight + ((_dimensions.y - _doorHeight) / 2.0f), 0.0f));
            doorTopper->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
            walls.push_back(doorTopper);
        }
    }
    else
    {
        auto eastWall = CreateWall(_core, glm::vec3(_dimensions.z, _dimensions.y, halfThickness), _wallTilingMultiplier);
        eastWall->GetTransform()->Translate(_centre + glm::vec3(-_dimensions.x / 2.0f, halfHeight, 0.0f));
        eastWall->GetTransform()->Rotate(90.0f, glm::vec3(0, 1, 0));
        walls.push_back(eastWall);
    }

    // Ceiling
    auto ceiling = _core->AddEntity();
    ceiling->AddComponent<eengine::ModelRenderer>("/data/models/ceiling/ceiling.obj")->SetTilingRatios(_dimensions.x / 5.0f, _dimensions.z / 5.0f);
    auto ceilingRb = ceiling->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(_dimensions.x, _wallThickness, _dimensions.z), 1.0f);
    ceilingRb->SetIsStatic(true);
    ceiling->GetTransform()->SetPosition(_centre + glm::vec3(0.0f, _dimensions.y + halfThickness, 0.0f));
    ceiling->GetTransform()->SetScale(_dimensions.x, _wallThickness, _dimensions.z);

    return walls;
}

int main(int argc, char* argv[])
{
 
    shared<eengine::Core> core = eengine::Core::Initialise(argv[0]);

    {
        auto floor = core->AddEntity();
        floor->GetTransform()->Translate(glm::vec3(0.8f, -0.25f, -5.0f));
        floor->GetTransform()->SetScale(50.0f, 0.5, 50.0f);
        auto floorRenderer = floor->AddComponent<eengine::ModelRenderer>("/data/models/concrete_floor/floor.obj");
        floorRenderer->SetTilingRatios(50, 50);
        auto rb = floor->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(100.0f, 0.5f, 100.0f), 1.0f);
        rb->SetFriction(1.5f);
        rb->SetIsStatic(true);

        // Starting room
        auto startingRoom = CreateRoom(core, glm::vec3(0,0,0), glm::vec3(10.0f, 3.0f, 10.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(true, true, true, false));

        // Weapon room
        auto weaponRoom = CreateRoom(core, glm::vec3(0,0,-10.0f), glm::vec3(10.0f, 2.0f, 10.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(false, false, true, false));
        auto weaponPickup = core->AddEntity();
        weaponPickup->AddComponent<eengine::ModelRenderer>("/data/models/tank/IS4.obj");
        auto pickupTrans = weaponPickup->GetTransform();
        pickupTrans->SetPosition(0.0f,0.5f,-10.0f);
        pickupTrans->SetScale(glm::vec3(0.2f));
        auto pickupRB = weaponPickup->AddComponent<eengine::RigidBody>(std::make_shared<eengine::SphereCollider>(0.2f), 1.0f);
        pickupRB->SetIsTrigger(true);
        //pickupRB->SetIsKinematic(true);
        weaponPickup->AddComponent<WeaponPickup>(0.3f, 45.0f, 45.0f);

        // Combat room
        auto combatRoom = CreateRoom(core, glm::vec3(15.0f,0,0), glm::vec3(20.0f, 15.0f, 30.0f), 0.1f, glm::vec2(2.0f), 1.0f, 2.0f, glm::bvec4(false, true, false, true));

        auto player = core->AddEntity();
        auto playerRB = player->AddComponent<eengine::RigidBody>(std::make_shared<eengine::CapsuleCollider>(0.2f, 0.6f), 1.0f);
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