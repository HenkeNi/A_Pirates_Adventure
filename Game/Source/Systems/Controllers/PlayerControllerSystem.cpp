#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "EntityManager.h"
#include "Controllers/ControllerComponents.h"
#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"


PlayerControllerSystem::PlayerControllerSystem()
{
}

PlayerControllerSystem::~PlayerControllerSystem()
{
}

void PlayerControllerSystem::Receive(Message& aMsg)
{
}

void PlayerControllerSystem::Update(float aDeltaTime)
{
	// Update the player based on which buttons are pressed... make sure to also set PlayerControllerComponent; like isJumping (so can't spamm)

	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<PlayerControllerComponent, InputComponent>();

	for (auto entity : entities)
	{
		auto controller = entity->GetComponent<PlayerControllerComponent>();
		auto input = entity->GetComponent<InputComponent>();
		auto velocity = entity->GetComponent<VelocityComponent>();

		if (input->m_inputStates[Hi_Engine::eInputType::Key_W])
		{
			velocity->m_velocity.z = -1;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_S])
		{
			velocity->m_velocity.z = 1;
		}
		else
		{ 
			velocity->m_velocity.z = 0;
		}



		if (input->m_inputStates[Hi_Engine::eInputType::Key_A])
		{
			velocity->m_velocity.x = -1;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_D])
		{
			velocity->m_velocity.x = 1;
		}
		else
		{
			velocity->m_velocity.x = 0;
		}


	}


}