#pragma once
#include "../../Transition/Transition.h"
 
class Entity;

// template with derived??
class State 
{
public:
	State();
	virtual ~State();

	virtual void	Init()						= 0;
	virtual void	Update(Entity* entity, float deltaTime)	= 0; // return State* ? dont pass in Entity here???
	//virtual State*	Update(float aDeltaTime)	= 0; // return State* ?

	virtual void	OnEnter()	{};
	virtual void	OnExit()	{};

	void			AddTransition(const Transition& transition);
	State*			GetDesiredState();
	void			Reset();

protected:
	std::vector<Transition> m_transitions;
	float					m_elapsedTime;
};