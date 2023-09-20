#pragma once
#include "../Base/State.h"


class WalkState : public State
{
public:
	void	Init()						override;
	State* Update(float aDeltaTime)		override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:
	float	m_elapsedTime;
};