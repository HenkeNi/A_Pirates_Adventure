#pragma once

class Entity;
class Condition;
class State;

class Transition
{
public:
	Transition();
	~Transition();

	void	SetCondition(Condition* condition);
	void	SetTargetState(State* state);
	void	SetPriority(unsigned priority);

	State*	GetTargetState()				const;
	bool	ShouldTransit(Entity* entity)	const;

	void	ResetCondition();
	void	Clear();

private:
	Condition*	m_condition;	// vector of multiple conditions? std::function instead?
	State*		m_targetState;
	unsigned	m_priority;
};