#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "EntityManager.h"
#include "Controllers/ControllerComponents.h"
#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include "Rendering/RenderComponents.h"


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

	auto entities = m_entityManager->FindAllWithComponents<PlayerControllerComponent, CharacterStateComponent, InputComponent>();

	for (auto entity : entities)
	{
		auto controller		= entity->GetComponent<PlayerControllerComponent>();
		auto characterState = entity->GetComponent<CharacterStateComponent>();
		auto input			= entity->GetComponent<InputComponent>();
		auto velocity		= entity->GetComponent<VelocityComponent>();

		bool isWalking = false;
		bool isAttacking = false;

		if (input->m_inputStates[Hi_Engine::eInputType::Key_W])
		{
			velocity->m_velocity.z = -1;
			characterState->m_isWalking = true;

			isWalking = true;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_S])
		{
			velocity->m_velocity.z = 1;
			isWalking = true;
		}
		else
		{ 
			velocity->m_velocity.z = 0;
		}



		if (input->m_inputStates[Hi_Engine::eInputType::Key_A])
		{
			velocity->m_velocity.x = -1;
			isWalking = true;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_D])
		{
			velocity->m_velocity.x = 1;
			isWalking = true;
		}
		else
		{
			velocity->m_velocity.x = 0;
		}


		if (isWalking)
			PostMaster::GetInstance().SendMessage({ eMessage::EntityWalking, entity });





		// TODO; listen to event instead??
		auto* attackCollider = entity->GetComponent<AttackColliderComponent>(); // TODO; Null check
		auto* rect = entity->GetComponent<RectComponent>();

		if (input->m_inputStates[Hi_Engine::eInputType::Key_Space])
		{
			PostMaster::GetInstance().SendMessage({ eMessage::EntityAttacking, entity });

			isAttacking = true;
			attackCollider->m_isEnabled = true;
			rect->m_color = { 0.f, 1.f, 0.f, 1.f };
		}
		else
		{
			attackCollider->m_isEnabled = false;
			rect->m_color = { 1.f, 0.f, 0.f, 1.f };
		}



		// Update position of attack collider...
		auto colliderWidth = attackCollider->m_collider.GetWidth();
		
		attackCollider->m_offset.x = velocity->m_velocity.x > 0.f ? colliderWidth : velocity->m_velocity.x < 0.f ? -colliderWidth : 0;
		attackCollider->m_offset.z = velocity->m_velocity.z > 0.f ? colliderWidth : velocity->m_velocity.z < 0.f ? -colliderWidth : 0;
		//attackCollider->m_offset.x = velocity->m_velocity.x;
		//attackCollider->m_offset.z = velocity->m_velocity.z;

		//if (velocity->m_velocity.z > 0)
		//	attackCollider->m_offset.z = 1.f;
		//else if (velocity->m_velocity.z < 0)
		//	attackCollider->m_offset.z = -1.f;
		//else
		//	attackCollider->m_offset.z = 0.f;

		//if (velocity->m_velocity.x > 0)
		//	attackCollider->m_offset.x = 1.f;
		//	//attackCollider->m_offset = { 1.f, 0.f, 0.f };
		//else if (velocity->m_velocity.x < 0)
		//	attackCollider->m_offset.x = -1.f;
		//else
		//	attackCollider->m_offset.x = 0.f;



		if (input->m_inputStates[Hi_Engine::eInputType::Key_Shift])
		{
			//velocity->m_acceleration = { 2.5f, 0.f, 2.5f };
			velocity->m_speed = 3.f;
		}
		else
		{
			//velocity->m_acceleration = { 1.f, 0.f, 1.f };
			velocity->m_speed = 1.f;
		}



		if (!isAttacking && !isWalking)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::EntityIdle, entity });
		}



		
	}


}