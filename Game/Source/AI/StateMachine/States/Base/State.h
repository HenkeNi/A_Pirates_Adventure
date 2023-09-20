#pragma once
#include "../../Transition/Transition.h"
 
// template with derived??
class State 
{
public:
	State();
	virtual ~State() = default;

	virtual void	Init()						= 0;
	virtual State*	Update(float aDeltaTime)	= 0; // return State* ?

	virtual void	OnEnter()	{};
	virtual void	OnExit()	{};

	void			AddTransition(const Transition& aTransition);

protected:
	std::vector<Transition> m_transitions;
};