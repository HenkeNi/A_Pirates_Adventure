#include "Pch.h"
#include "WalkState.h"
#include "Entities/Entity.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"

void WalkState::Init()
{}

void WalkState::Update(Entity* anEntity, float aDeltaTime)
{
	m_elapsedTime += aDeltaTime;

	//std::cout << "Walking..\n";

	if (auto* blackboard = anEntity->GetComponent<BlackboardComponent>())
	{
		auto* transform = anEntity->GetComponent<TransformComponent>();
		auto* velocity = anEntity->GetComponent<VelocityComponent>();

		const auto currentPos = transform->CurrentPos;
		const auto desiredPosition = blackboard->PlayerPosition;
	
		velocity->Velocity = desiredPosition - currentPos;
		

	}


	// FUNCTION?
	/*for (const auto& transition : m_transitions)
	{
		if (transition.ShouldTransit(m_elapsedTime))
		{
			return transition.GetTargetState();
		}
	}

	return this;*/
}

void WalkState::OnEnter()
{
	//m_elapsedTime = 0.f;
}

void WalkState::OnExit()
{
	std::cout << m_elapsedTime << "\n";
}
