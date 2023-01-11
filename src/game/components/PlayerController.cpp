#include "PlayerController.h"
#include "Suicider.h"

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
	m_viewAngleLimit = 90.0f;
	m_hasWeapon = false;
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
	bool upperHalf = glm::dot(-camTransform->Forward(), glm::vec3(0, 1, 0)) > 0;
	if ( angleBetween + (upperHalf ? -(sensitivity * delta.y) : sensitivity * delta.y) > m_viewAngleLimit)
	{
		float vertRotation = upperHalf ? (m_viewAngleLimit - angleBetween) : -(m_viewAngleLimit - angleBetween);
		camTransform->Rotate(vertRotation, camTransform->Right());		
	}
	else 
	{
		camTransform->Rotate(-(sensitivity * delta.y), camTransform->Right());
	}

	// Transform weapon renderer
	if (m_hasWeapon) 
	{
		glm::vec3 finalOffset = glm::toMat4(camTransform->GetQuaternionRotation()) * glm::vec4(m_weaponOffset, 1.0f);
		m_weaponTransform->SetPosition(camTransform->GetPosition() + finalOffset);
		m_weaponTransform->SetRotation(camTransform->GetQuaternionRotation());
	}
	

	glm::vec3 oldVel = m_rigidBody->GetVelocity();
	glm::vec3 newVel = oldVel;
	float verticalVel = newVel.y;
	newVel.y = 0;

	if (input->GetKey(eengine::KeyCode::w))
	{
		newVel += (m_playerSpeed * -m_transform->Forward());
	}
	if (input->GetKey(eengine::KeyCode::s))
	{
		newVel += (m_playerSpeed * m_transform->Forward());
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
	

	if (input->GetMouse1Down())
	{
		auto e = GetCore()->AddEntity();
		auto rb = e->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(1.0f, 1.0f, 1.0f), 10.0f);
		e->AddComponent<eengine::ModelRenderer>("/data/models/crate/Crate1.obj");
		glm::vec3 scale(1.0f, 1.0f, 1.0f);
		e->GetTransform()->SetScale(scale);
		rb->SetColliderScale(scale);
		e->GetTransform()->SetPosition(camTransform->GetPosition() - camTransform->Forward() * 1.0f);
		auto as = e->AddComponent<eengine::AudioSource>();
		//as->PlayOneShot(GetCore()->GetResources()->Load<eengine::Sound>("/data/audio/dixie_horn.ogg"));
		as->SetVolume(1.5f);
		e->AddComponent<Suicider>();

		rb->SetVelocity(m_rigidBody->GetVelocity());
		rb->ApplyImpulse(100.0f * -camTransform->Forward(), e->GetTransform()->GetPosition() - camTransform->GetPosition());
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