#include "Pch.h"
#include "WalkState.h"
#include "Entities/Entity.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"

void WalkState::Init()
{}

void WalkState::Update(Entity* entity)
{
 	// m_elapsedTime += deltaTime;

	//std::cout << "Walking..\n";

	if (auto* blackboard = entity->GetComponent<BlackboardComponent>())
	{
		auto* transform = entity->GetComponent<TransformComponent>();
		auto* velocity = entity->GetComponent<VelocityComponent>();

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
	//std::cout << m_elapsedTime << "\n";
}
