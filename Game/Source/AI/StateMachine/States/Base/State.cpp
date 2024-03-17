#include "Pch.h"
#include "State.h"


State::State()
	: m_elapsedTime{ 0.f }
{
}

State::~State()
{
	for (auto& transition : m_transitions)
	{
		transition.Reset();
	}
}

void State::AddTransition(const Transition& transition)
{
	m_transitions.push_back(transition);
}

State* State::GetDesiredState()
{
	for (auto& transition : m_transitions)
	{
		if (transition.ShouldTransit(m_elapsedTime))
		{
			return transition.GetTargetState();
		}
	}
	//return this;
	return nullptr;
}

void State::Reset()
{
	m_elapsedTime = 0.f;
}