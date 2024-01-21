#pragma once

class Condition;
class State;

class Transition
{
public:
	Transition();
	~Transition();

	void	SetCondition(Condition* aCondition);
	void	SetTargetState(State* aState);
	void	SetPriority(unsigned aPriority);

	State*	GetTargetState()					const;
	bool	ShouldTransit(float elapsedTime)	const;

	void	Reset();

private:
	Condition*	m_condition;	// vector of multiple conditions? std::function instead?
	State*		m_targetState;
	unsigned	m_priority;
};