#include "Pch.h"
#include "WalkState.h"


void WalkState::Init()
{}

State* WalkState::Update(float aDeltaTime)
{
	m_elapsedTime += aDeltaTime;

	std::cout << "Walking..\n";

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

void WalkState::OnEnter()
{
	m_elapsedTime = 0.f;
}

void WalkState::OnExit()
{}
