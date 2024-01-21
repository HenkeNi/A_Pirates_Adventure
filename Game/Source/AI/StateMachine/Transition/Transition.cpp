#include "Pch.h"
#include "Transition.h"
#include "../Conditions/Base/Condition.h"


Transition::Transition()
	: m_targetState{ nullptr }, m_priority{ 0 }
{
}

Transition::~Transition()
{
}

void Transition::SetCondition(Condition* aCondition)
{
	m_condition = aCondition;
}

void Transition::SetTargetState(State* aState)
{
	m_targetState = aState;
}

void Transition::SetPriority(unsigned aPriority)
{
	m_priority = aPriority;
}

State* Transition::GetTargetState() const
{
	auto* target = m_targetState;
	return m_targetState;
}

bool Transition::ShouldTransit(float elapsedTime) const
{
	return m_condition->IsSatisfied(elapsedTime);
}

void Transition::Reset()
{
	if (m_condition)
		delete m_condition;

	m_condition = nullptr;
	m_targetState = nullptr;
}