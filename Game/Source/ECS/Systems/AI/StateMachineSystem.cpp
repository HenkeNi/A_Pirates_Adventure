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

void StateMachineSystem::Receive(Message& aMsg)
{
}

void StateMachineSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<StateMachineComponent>();

	for (auto& entity : entities)
	{
		auto* stateMachineComponent = entity->GetComponent<StateMachineComponent>();

		if (auto* activeState = stateMachineComponent->ActiveState)
		{
			activeState = activeState->Update(aDeltaTime);

			



			// IdleState (bottom, default)... WalkState... AttackState...

		}
	}
}