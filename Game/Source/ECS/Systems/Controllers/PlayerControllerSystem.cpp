#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

#include "../Commands/Sprint/SprintCommand.h"
#include "Commands/Attack/AttackCommand.h"	
#include "Commands/Move/MoveCommand.h"


PlayerControllerSystem::PlayerControllerSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

PlayerControllerSystem::~PlayerControllerSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void PlayerControllerSystem::Receive(Message& aMsg)
{
	InitCommands();
}

void PlayerControllerSystem::Update(float aDeltaTime)
{
	// Update the player based on which buttons are pressed... make sure to also set PlayerControllerComponent; like isJumping (so can't spamm)

	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<PlayerControllerComponent, CharacterStateComponent, InputComponent>();

	for (auto entity : entities)
	{
		auto id = entity;

		auto controller		= entity->GetComponent<PlayerControllerComponent>();
		auto characterState = entity->GetComponent<CharacterStateComponent>();
		auto input			= entity->GetComponent<InputComponent>();
		auto velocity		= entity->GetComponent<VelocityComponent>();


		//characterState->m_isIdle = true;

		for (const auto& command : controller->InputMapping)
		{
			if (input->InputStates[command.first])
			{
				command.second->Execute();
			}
		}


		// TEMP
		// m_velocity = 

		if (Hi_Engine::InputHandler::IsKeyPressed(Hi_Engine::eKey::Key_R))
			entity->GetComponent<TransformComponent>()->CurrentPos = { 27.f, 0.42f, 25.f };

		// TODO; Decrease in MovementSystem; 
		if (input->InputStates[Hi_Engine::eKey::Key_LShift])
		{
			//velocity->m_acceleration = { 2.5f, 0.f, 2.5f };
			// velocity->m_speed = 3.f;
		}
		else
		{
			//velocity->m_acceleration = { 1.f, 0.f, 1.f };
			velocity->Speed = 1.f;
			characterState->IsRunning = false;
		}


		// Update position of attack collider...
	/*	auto colliderWidth = attackCollider->m_collider.GetWidth();

		attackCollider->m_offset.x = velocity->m_velocity.x > 0.f ? colliderWidth : velocity->m_velocity.x < 0.f ? -colliderWidth : 0;
		attackCollider->m_offset.z = velocity->m_velocity.z > 0.f ? colliderWidth : velocity->m_velocity.z < 0.f ? -colliderWidth : 0;
*/











		/*if (input->m_inputStates[Hi_Engine::eInputType::Key_W])
		{
			velocity->m_velocity.z = -1;
			characterState->m_isWalking = true;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_S])
		{
			velocity->m_velocity.z = 1;
			characterState->m_isWalking = true;
		}
		else
		{ 
			velocity->m_velocity.z = 0;
		}


		if (input->m_inputStates[Hi_Engine::eInputType::Key_A])
		{
			velocity->m_velocity.x = -1;
			characterState->m_isWalking = true;
		}
		else if (input->m_inputStates[Hi_Engine::eInputType::Key_D])
		{
			velocity->m_velocity.x = 1;
			characterState->m_isWalking = true;
		}
		else
		{
			velocity->m_velocity.x = 0;
		}*/


		



		// TODO; listen to event instead??
		//auto* attackCollider = entity->GetComponent<AttackColliderComponent>(); // TODO; Null check
		//auto* rect = entity->GetComponent<RectComponent>();

		//if (input->m_inputStates[Hi_Engine::eInputType::Key_Space])
		//{
		//	if (!characterState->m_isAttacking)
		//	{
		//		characterState->m_isAttacking = true;
		//		
		//		attackCollider->m_isEnabled = true;		 // HERE??
		//		rect->m_color = { 0.f, 1.f, 0.f, 1.f };  // HERE??
		//	}
		//}
		//else
		//{
		//	attackCollider->m_isEnabled = false;		// HERE
		//	rect->m_color = { 1.f, 0.f, 0.f, 1.f };		// HERE
		//}



		



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



		


		// TODO; check near equal instead.. Or dont use velicuty??
		if (velocity->Velocity.x == 0.f && velocity->Velocity.z == 0.f)
		{
			characterState->IsWalking = false;
			
			if (!characterState->IsAttacking)
			{
				characterState->IsIdle = true;
			}
		}
		else
			characterState->IsIdle = false;


		
	}


}


void PlayerControllerSystem::InitCommands()
{
	auto entities = m_entityManager->FindAll<PlayerControllerComponent, CharacterStateComponent, InputComponent>();

	for (auto entity : entities)
	{
		auto playerController = entity->GetComponent<PlayerControllerComponent>();

		for (auto command : playerController->InputMapping)
		{
			// TODO; fix...
			if (command.first == Hi_Engine::eKey::Key_W || command.first == Hi_Engine::eKey::Key_S ||
				command.first == Hi_Engine::eKey::Key_A || command.first == Hi_Engine::eKey::Key_D)
			{
				auto moveCommand = static_cast<MoveCommand*>(command.second);

				moveCommand->SetComponents(entity->GetComponent<VelocityComponent>(), entity->GetComponent<CharacterStateComponent>());
			}

			if (command.first == Hi_Engine::eKey::Key_Space)
			{
				auto attackCommand = static_cast<AttackCommand*>(command.second);

				attackCommand->SetComponent(entity->GetComponent<AttackComponent>(), entity->GetComponent<CharacterStateComponent>(), entity->GetComponent<DebugRectComponent>());
			}

			if (command.first == Hi_Engine::eKey::Key_LShift)
			{
				auto sprintCommand = static_cast<SprintCommand*>(command.second);
				sprintCommand->SetComponent(entity->GetComponent<VelocityComponent>(), entity->GetComponent<CharacterStateComponent>());
			}
		}
	}

}