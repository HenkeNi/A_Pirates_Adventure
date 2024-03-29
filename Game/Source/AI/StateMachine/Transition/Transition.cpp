#include "Pch.h"
#include "Transition.h"
#include "../Conditions/Base/Condition.h"


Transition::Transition()
	: m_condition{ nullptr }, m_targetState{ nullptr }, m_priority{ 0 }
{
}

Transition::~Transition()
{
}

void Transition::SetCondition(Condition* condition)
{
	m_condition = condition;
}

void Transition::SetTargetState(State* state)
{
	m_targetState = state;
}

void Transition::SetPriority(unsigned priority)
{
	m_priority = priority;
}

State* Transition::GetTargetState() const
{
	auto* target = m_targetState;
	return m_targetState;
}

bool Transition::ShouldTransit(Entity* entity) const
{
	return m_condition->IsSatisfied(entity);
}

void Transition::ResetCondition()
{
	if (m_condition)
		m_condition->Reset();
}

void Transition::Clear()
{
	if (m_condition)
		delete m_condition;

	m_condition = nullptr;
	m_targetState = nullptr;
}