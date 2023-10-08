#include "Pch.h"
#include "IdleState.h"
#include "../../Transition/Transition.h"


void IdleState::Init()
{
}

State* IdleState::Update(float aDeltaTime)
{
	m_elapsedTime += aDeltaTime;

	//std::cout << "Ideling..\n";


	// FUNCTION?
	for (const auto& transition : m_transitions)
	{
		if (transition.ShouldTransit(m_elapsedTime))
		{
			return transition.GetTargetState();
		}
	}

	return this;
}

void IdleState::OnEnter() 
{
	m_elapsedTime = 0.f;
	// set velocity...
}

void IdleState::OnExit() 
{
}