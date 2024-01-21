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
		auto* stateMachine = entity->GetComponent<StateMachineComponent>();

		if (auto* activeState = stateMachine->ActiveState) // maybe becvause local pointer?
		{
			activeState->Update(entity, aDeltaTime);

			if (auto* desiredState = activeState->GetDesiredState())
			{
				activeState->OnExit();
				activeState->Reset();

				stateMachine->ActiveState = desiredState;
				desiredState->OnEnter();
			}

			// stateMachine->ActiveState = activeState->GetDesiredState();

			//if (auto* desiredState = activeState->GetDesiredState())
			//{
			//	stateMachine->ActiveState = desiredState;
			//}

			// if should transition...
			//if ()
			//{ }

			//stateMachine->ActiveState = activeState->Update(aDeltaTime);

			//if (!activeState)
			//	std::cout << "ERROR\n";

			//stateMachine->ActiveState = activeState; // Why work?

			// IdleState (bottom, default)... WalkState... AttackState...

		}
	}
}