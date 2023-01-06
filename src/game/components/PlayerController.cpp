#include "PlayerController.h"

#include <eengine/eengine.h>

void PlayerController::OnBegin() 
{
	m_rigidBody = GetParent()->GetComponentOfType<eengine::RigidBody>();
	m_transform = GetParent()->GetTransform();
	m_playerSpeed = 4.0f;
	m_camOffset = glm::vec3(0.0f, 0.4f, 0.0f);
}

void PlayerController::OnTick(float _deltaTime) 
{
	auto input = GetInput();

	auto delta = input->GetMouseDelta();
	float sensitivity = input->GetMouseSensitivity();

	m_transform->Rotate(-sensitivity * delta.x, glm::vec3(0, 1, 0));
	//m_transform->Rotate(-sensitivity * delta.y, m_transform->Right());

	glm::vec3 newVel = m_rigidBody->GetVelocity();
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
		newVel += (m_playerSpeed  * -m_transform->Right());
	}
	if (input->GetKey(eengine::KeyCode::d))
	{
		newVel += (m_playerSpeed * m_transform->Right());
	}

	if (input->Mouse1Down()) 
	{
		auto e = GetCore()->AddEntity();
		auto rb = e->AddComponent<eengine::RigidBody>(std::make_shared<eengine::BoxCollider>(0.125f, 0.125f, 0.125f), 10.0f);
		e->AddComponent<eengine::ModelRenderer>("/data/models/crate/UnitCube.obj");
		e->GetTransform()->SetScale(0.125f,0.125f,0.125f);
		e->GetTransform()->SetPosition(m_transform->GetPosition() - m_transform->Forward() * 2.0f);

		rb->ApplyImpulse(100.0f * -m_transform->Forward(), e->GetTransform()->GetPosition() - m_transform->GetPosition());
	}

	if (glm::length(newVel) != 0) 
	{
		newVel = glm::length(newVel) > m_playerSpeed ? glm::normalize(newVel) * m_playerSpeed : newVel;
		newVel.y = verticalVel;
		m_rigidBody->SetVelocity(newVel);
	}

	if (input->GetKeyDown(eengine::KeyCode::space))
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
	mainCamTransform->SetRotation(m_transform->GetQuaternionRotation());

	//eengine::Debug::Log("Forward", m_transform->Forward());
}