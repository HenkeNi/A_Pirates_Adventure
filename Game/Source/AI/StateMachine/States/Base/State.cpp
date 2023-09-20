#include "Pch.h"
#include "State.h"


State::State()
{
}

void State::AddTransition(const Transition& aTransition)
{
	m_transitions.push_back(aTransition);
}