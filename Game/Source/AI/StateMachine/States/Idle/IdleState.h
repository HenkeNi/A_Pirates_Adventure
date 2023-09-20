#pragma once
#include "../Base/State.h"


class IdleState : public State
{
public:
	void	Init()						override;
	State*	Update(float aDeltaTime)	override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:
	float	m_elapsedTime;
};