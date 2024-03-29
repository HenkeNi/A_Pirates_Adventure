#pragma once
#include "../../Transition/Transition.h"
 
class Entity;

// template with derived??
class State 
{
public:
	State();
	virtual ~State();

	virtual void	Init()					= 0;
	virtual void	Update(Entity* entity)	= 0;	// return State* ?

	virtual void	OnEnter()	{};
	virtual void	OnExit()	{};

	State*			GetDesiredState(Entity* entity);
	void			AddTransition(const Transition& transition);
	void			Reset();

protected:
	std::vector<Transition> m_transitions;
	//float					m_elapsedTime;
};