#include "Pch.h"
#include "StateMachineSystem.h"
#include "Entities/EntityManager.h"
#include "../AI/StateMachine/States/Base/State.h"
#include "Components/AI/AIComponents.h"


StateMachineSystem::StateMachineSystem()
{
}

StateMachineSystem::~StateMachineSystem()
{
}

void StateMachineSystem::Receive(Message& message)
{
}

void StateMachineSystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<StateMachineComponent>();

	for (auto& entity : entities)
	{
		UpdateCurrentState(entity);
	}
}

void StateMachineSystem::UpdateCurrentState(Entity* entity)
{
	auto* stateMachine = entity->GetComponent<StateMachineComponent>();

	if (auto* activeState = stateMachine->ActiveState)
	{
		activeState->Update(entity);

		if (auto* desiredState = activeState->GetDesiredState(entity))
		{
			activeState->OnExit();

			stateMachine->ActiveState = desiredState;
			desiredState->Reset();
			desiredState->OnEnter();
		}
	}
}