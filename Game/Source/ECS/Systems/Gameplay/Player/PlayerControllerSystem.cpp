#include "Pch.h"
#include "PlayerControllerSystem.h"
#include "ECS.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


PlayerControllerSystem::PlayerControllerSystem()
{
}

PlayerControllerSystem::~PlayerControllerSystem()
{
}

void PlayerControllerSystem::Update(float deltaTime)
{
	assert(m_ecs && "[PlayerControllerSystem::Update] - ECS is not initialized!");

	for (auto entity : m_ecs->FindEntities(m_signatures["Player"]))
	{
		GenerateCommands(entity);
	}
}

void PlayerControllerSystem::SetSignature()
{
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent, InputComponent, CommandQueueComponent>() });
}

void PlayerControllerSystem::GenerateCommands(Entity entity)
{
	auto* commandQueueComponent = m_ecs->GetComponent<CommandQueueComponent>(entity);
	auto* playerControllerComponent = m_ecs->GetComponent<PlayerControllerComponent>(entity);
	auto* inputComponent = m_ecs->GetComponent<InputComponent>(entity);

	for (const auto& [input, command] : playerControllerComponent->InputMapping)
	{
		//auto inputState = inputComponent->InputStates.find(input);
		//if (inputState != inputComponent->InputStates.end())
		if (inputComponent->InputStates[input])
		{
			// create command
		/*	Command command;
			command.Type = commandType;
			SetCommandData(command);*/

			commandQueueComponent->Commands.push(command);
		}
	}
}