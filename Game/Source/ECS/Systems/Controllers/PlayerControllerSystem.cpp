#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "ECS.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

#include "../Commands/Sprint/SprintCommand.h"
#include "Commands/Attack/AttackCommand.h"	
#include "Commands/Move/MoveCommand.h"


PlayerControllerSystem::PlayerControllerSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::AttackAnimationFinished, this);
}

PlayerControllerSystem::~PlayerControllerSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::AttackAnimationFinished, this);
	CleanUpCommands();
}

void PlayerControllerSystem::Receive(Message& message)
{
	auto entity = std::any_cast<Entity>(message.GetData());

	if (auto* characterStateComponent = m_ecs->GetComponent<CharacterStateComponent>(entity))
	{
		characterStateComponent->IsAttacking = false;
	}
}

void PlayerControllerSystem::Update(float deltaTime)
{
	assert(m_ecs && "ERROR: ECS is nullptr!");

	auto entities = m_ecs->FindEntities(m_signatures["Player"]);

	for (auto entity : entities)
	{
		ProcessCommands(entity);
		UpdatePlayerState(entity);		
	}
}

void PlayerControllerSystem::SetSignature()
{
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent, CharacterStateComponent, InputComponent>() });
}

void PlayerControllerSystem::ProcessCommands(Entity entity)
{
	auto* playerControllerComponent = m_ecs->GetComponent<PlayerControllerComponent>(entity);
	auto* inputComponent			= m_ecs->GetComponent<InputComponent>(entity);

	if (!playerControllerComponent || !inputComponent)
		return;

	for (const auto& [key, command] : playerControllerComponent->InputMapping)
	{
		// TODO: dont do input check? check in component instead?? store commands in simple array?
		bool isKeyActive = inputComponent->InputStates[key]; // NOTE: this will add the releveant keys to the map.. (maybe use .find, or .at and initialize keys when creating the component?
		//bool canPerform = command->CanPerform(entity);

		isKeyActive ? command->Execute(entity, *m_ecs) : command->Undo(entity, *m_ecs);
	}
}

void PlayerControllerSystem::CleanUpCommands()
{
	auto playerControllers = m_ecs->FindEntities(m_signatures["Player"]);

	for (auto playerController : playerControllers)
	{
		auto* playerControllerComponent = m_ecs->GetComponent<PlayerControllerComponent>(playerController);

		for (auto& [key, command] : playerControllerComponent->InputMapping)
		{
			delete command;
		}
	}
}

void PlayerControllerSystem::UpdateCooldowns(Entity entity)
{
}

void PlayerControllerSystem::UpdatePlayerState(Entity entity) // dO in commands?
{
	auto* characterStateComponent	= m_ecs->GetComponent<CharacterStateComponent>(entity);
	auto* velocityComponent			= m_ecs->GetComponent<VelocityComponent>(entity);

	if (!characterStateComponent || !velocityComponent)
		return;

	// TODO: check close to 0 instead (use Utility function)
	bool isMoving = velocityComponent->Velocity.x != 0.f || velocityComponent->Velocity.y != 0.f;

	characterStateComponent->IsIdle = !characterStateComponent->IsAttacking && !isMoving;
	characterStateComponent->IsWalking = isMoving;

	// characterStateComponent->IsRunning = true;
}