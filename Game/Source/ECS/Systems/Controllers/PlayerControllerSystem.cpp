#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "Entities/EntityManager.h"
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

void PlayerControllerSystem::Receive(Message& aMsg)
{
	auto* entity = std::any_cast<Entity*>(aMsg.GetData());

	if (!entity)
		return;

	if (entity->HasComponents<PlayerControllerComponent, CharacterStateComponent>())
	{
		auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>();
		characterStateComponent->IsAttacking = false;
	}

}

void PlayerControllerSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<PlayerControllerComponent, CharacterStateComponent, InputComponent>();

	for (auto* entity : entities)
	{
		ProcessCommands(entity);
		UpdatePlayerState(entity);		
	}
}

void PlayerControllerSystem::ProcessCommands(Entity* anEntity)
{
	if (!anEntity)
		return;

	auto* playerControllerComponent = anEntity->GetComponent<PlayerControllerComponent>();
	auto* inputComponent			= anEntity->GetComponent<InputComponent>();

	if (!playerControllerComponent || !inputComponent)
		return;

	for (const auto& [key, command] : playerControllerComponent->InputMapping)
	{
		// TODO: dont do input check? check in component instead?? store commands in simple array?
		bool isKeyActive = inputComponent->InputStates[key]; // NOTE: this will add the releveant keys to the map.. (maybe use .find, or .at and initialize keys when creating the component?
		//bool canPerform = command->CanPerform(anEntity);

		isKeyActive ? command->Execute(anEntity) : command->Undo(anEntity);
	}
}

void PlayerControllerSystem::CleanUpCommands()
{
	auto playerControllers = m_entityManager->FindAll<PlayerControllerComponent>();

	for (auto& playerController : playerControllers)
	{
		auto* playerControllerComponent = playerController->GetComponent<PlayerControllerComponent>();

		for (auto& [key, command] : playerControllerComponent->InputMapping)
		{
			delete command;
		}
	}
}

void PlayerControllerSystem::UpdatePlayerState(Entity* anEntity) // dO in commands?
{
	if (!anEntity)
		return;

	auto* characterStateComponent	= anEntity->GetComponent<CharacterStateComponent>();
	auto* velocityComponent			= anEntity->GetComponent<VelocityComponent>();

	if (!characterStateComponent || !velocityComponent)
		return;

	// TODO: check close to 0 instead (use Utility function)
	bool isMoving = velocityComponent->Velocity.x != 0.f || velocityComponent->Velocity.y != 0.f;

	characterStateComponent->IsIdle = !characterStateComponent->IsAttacking && !isMoving;
	characterStateComponent->IsWalking = isMoving;

	// characterStateComponent->IsRunning = true;
}