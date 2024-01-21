#pragma once
#include "../Base/State.h"


class IdleState : public State
{
public:
	void	Init()						override;
	void	Update(Entity* anEntity, float aDeltaTime)	override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:
	//float	m_elapsedTime;
};