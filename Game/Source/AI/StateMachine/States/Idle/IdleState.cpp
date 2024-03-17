#include "Pch.h"
#include "IdleState.h"
#include "../../Transition/Transition.h"


void IdleState::Init()
{
}

void IdleState::Update(Entity* entity, float deltaTime)
{
	m_elapsedTime += deltaTime; // Dont want to do this in every state...

	//std::cout << "Ideling..\n";
	//std::cout << "Idle\n";

	// FUNCTION?
	/*for (const auto& transition : m_transitions)
	{
		if (transition.ShouldTransit(m_elapsedTime))
		{
			return transition.GetTargetState();
		}
	}*/

	/*if (auto* desiredState = GetDesiredStat(m_elapsedTime))
		return desiredState;

	return this;*/
}

void IdleState::OnEnter() 
{
	//m_elapsedTime = 0.f;
	// set velocity...
}

void IdleState::OnExit() 
{
	std::cout << m_elapsedTime << "\n";
}