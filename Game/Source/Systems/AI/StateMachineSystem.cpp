#include "Pch.h"
#include "StateMachineSystem.h"
#include "EntityManager.h"
#include "../AI/StateMachine/States/Base/State.h"


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

	auto entities = m_entityManager->FindAllWithComponents<StateMachineComponent>();

	for (auto& entity : entities)
	{
		auto* stateMachineComponent = entity->GetComponent<StateMachineComponent>();

		if (auto* activeState = stateMachineComponent->m_activeState)
		{
			activeState = activeState->Update(aDeltaTime);

			



			// IdleState (bottom, default)... WalkState... AttackState...

		}
	}
}