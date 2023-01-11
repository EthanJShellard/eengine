#include "PlayerController.h"
#include "RocketController.h"

#include <eengine/eengine.h>

void PlayerController::OnBegin() 
{
	m_rigidBody = GetParent()->GetComponentOfType<eengine::RigidBody>();
	m_transform = GetParent()->GetTransform();
	m_playerSpeed = 4.0f;
	m_aerialSpeed = 2.0f;
	m_camOffset = glm::vec3(0.0f, 0.4f, 0.0f);
	m_weaponOffset = glm::vec3(0.1f, -0.15f, -0.3f);
	m_weaponScale = glm::vec3(0.04f, 0.04f, 0.04f);
	m_rocketScale = glm::vec3(0.5f, 0.5f, 0.5f);
	m_rocketSpeed = 15.0f;
	m_rocketColliderScale = glm::vec3(0.131f, 0.131, 1.0f);
	m_viewAngleLimit = 90.0f;
	m_hasWeapon = false;

	// Create rocket
	auto rocket = GetCore()->AddEntity();
	m_rocketRigidBody = rocket->AddComponent<eengine::RigidBody>
		(
			std::make_shared<eengine::BoxCollider>(
				m_rocketScale.x * m_rocketColliderScale.x,
				m_rocketScale.y * m_rocketColliderScale.y,
				m_rocketScale.z * m_rocketColliderScale.z
				),
			10.0f
			);
	m_rocketRigidBody->SetRotationAxesLocked(true, true, true);
	m_rocketRigidBody->SetIsTrigger(true);
	m_rocketRigidBody->SetGravity(glm::vec3(0));
	m_rocketTransform = rocket->GetTransform();
	m_rocketTransform->SetScale(m_rocketScale);
	m_rocketAudioSource = rocket->AddComponent<eengine::AudioSource>();
	rocket->AddComponent<eengine::ModelRenderer>("/data/models/rpg/rpg.obj");
	rocket->AddComponent<RocketController>(4.0f);
	rocket->Disable();

	m_rocketBoostSound = GetCore()->GetResources()->Load<eengine::Sound>("/data/audio/rocket/boost.ogg");
	m_rocketBoostSound->SetDirectional(true);
}

void PlayerController::OnTick(float _deltaTime) 
{
	auto input = GetInput();

	auto delta = input->GetMouseDelta();
	float sensitivity = input->GetMouseSensitivity();

	m_transform->Rotate(-sensitivity * delta.x, glm::vec3(0, 1, 0));

	// very much imperfect but will do for now
	bool grounded = GetCore()->GetPhysicsContext()->RayCast(m_transform->GetPosition(), glm::vec3(0, -1, 0), 0.51f).didHit;
	
	// Camera yaw
	auto camTransform = GetCore()->GetMainCamera()->m_transform;
	camTransform->Rotate(-sensitivity * delta.x, glm::vec3(0, 1, 0));
	// Clamped camera pitch
	float viewDot = glm::dot(camTransform->Forward(), m_transform->Forward());
	float angleBetween = glm::degrees(std::acos(viewDot));
	bool upperHalf = glm::dot(camTransform->Forward(), glm::vec3(0, 1, 0)) > 0;
	if ( angleBetween + (upperHalf ? -(sensitivity * delta.y) : sensitivity * delta.y) > m_viewAngleLimit)
	{
		float vertRotation = upperHalf ? (m_viewAngleLimit - angleBetween) : -(m_viewAngleLimit - angleBetween);
		camTransform->Rotate(vertRotation, camTransform->Right());		
	}
	else 
	{
		camTransform->Rotate(-(sensitivity * delta.y), camTransform->Right());
	}

	if (m_hasWeapon) 
	{
		// Weapon firing
		if (input->GetMouse1Down() && !m_rocketTransform->GetParent()->GetEnabled())
		{
			m_rocketTransform->GetParent()->Enable();

			m_rocketTransform->SetPosition(m_weaponTransform->GetPosition() + (m_weaponTransform->Forward() * 0.5f));
			m_rocketTransform->SetRotation(camTransform->GetQuaternionRotation());//glm::rotate(camTransform->GetQuaternionRotation(), glm::radians(-90.0f), camTransform->Up()));

			m_rocketRigidBody->SetVelocity(camTransform->Forward() * m_rocketSpeed);

			m_rocketAudioSource->PlayOneShot(m_rocketBoostSound);
			m_rocketAudioSource->SetLooping(true);
		}
	}
	

	glm::vec3 oldVel = m_rigidBody->GetVelocity();
	glm::vec3 newVel = oldVel;
	float verticalVel = newVel.y;
	newVel.y = 0;

	if (input->GetKey(eengine::KeyCode::w))
	{
		newVel += (m_playerSpeed * m_transform->Forward());
	}
	if (input->GetKey(eengine::KeyCode::s))
	{
		newVel += (m_playerSpeed * -m_transform->Forward());
	}
	if (input->GetKey(eengine::KeyCode::a))
	{
		newVel += (m_playerSpeed * -m_transform->Right());
	}
	if (input->GetKey(eengine::KeyCode::d))
	{
		newVel += (m_playerSpeed * m_transform->Right());
	}

	if (glm::length(newVel) != 0)
	{
		newVel = glm::length(newVel) > m_playerSpeed ? glm::normalize(newVel) * m_playerSpeed : newVel;
		newVel.y = verticalVel;
		if (!grounded) 
		{
			newVel = glm::mix(oldVel, newVel, _deltaTime * m_aerialSpeed);
		}
		m_rigidBody->SetVelocity(newVel);
	}

	if (input->GetKeyDown(eengine::KeyCode::space) && grounded)
	{
		m_rigidBody->ApplyImpulse(glm::vec3(0, 5, 0), glm::vec3(0, -1, 0));
	}

	if (input->GetKey(eengine::KeyCode::escape))
	{
		GetCore()->Stop();
	}
}

void PlayerController::OnLateTick(float _deltaTime) 
{
	// Pin camera to this entity
	auto mainCamTransform = GetCore()->GetMainCamera()->m_transform;
	mainCamTransform->SetPosition(m_transform->GetPosition() + m_camOffset);

	if (m_hasWeapon)
	{
		// Transform weapon renderer
		glm::vec3 finalOffset = glm::toMat4(mainCamTransform->GetQuaternionRotation()) * glm::vec4(m_weaponOffset, 1.0f);
		m_weaponTransform->SetPosition(mainCamTransform->GetPosition() + finalOffset);
		m_weaponTransform->SetRotation(mainCamTransform->GetQuaternionRotation());
	}
}

void PlayerController::GiveWeapon() 
{
	auto weapon = GetCore()->AddEntity();
	m_weaponRenderer = weapon->AddComponent<eengine::ModelRenderer>("/data/models/tank/IS4.obj");
	m_weaponTransform = weapon->GetTransform();
	m_hasWeapon = true;
	m_weaponRenderer->SetScale(m_weaponScale);
	m_weaponRenderer->SetOrientation(glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

}