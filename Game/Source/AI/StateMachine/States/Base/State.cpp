#include "Pch.h"
#include "State.h"


State::State()
//	: m_elapsedTime{ 0.f }
{
}

State::~State()
{
	for (auto& transition : m_transitions)
	{
		transition.Clear();
	}
}

State* State::GetDesiredState(Entity* entity)
{
	for (auto& transition : m_transitions)
	{
		if (transition.ShouldTransit(entity))
		{
			return transition.GetTargetState();
		}
	}
	//return this;
	return nullptr;
}

void State::AddTransition(const Transition& transition)
{
	m_transitions.push_back(transition);
}

void State::Reset()
{
	//m_elapsedTime = 0.f;
	for (auto& transition : m_transitions)
	{
		transition.ResetCondition();
	}
}