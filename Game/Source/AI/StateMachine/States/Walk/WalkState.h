#pragma once
#include "../Base/State.h"


// rename WalkTowards?? Separate for patrolling and walk towards?? Walkt towards taget?? how to set target?
class WalkState : public State
{
public:
	void	Init()						override;
	void	Update(Entity* entity, float deltaTime)	override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:
	//float	m_elapsedTime;
};