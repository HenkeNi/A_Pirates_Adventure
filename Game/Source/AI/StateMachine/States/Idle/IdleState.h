#pragma once
#include "../Base/State.h"


class IdleState : public State
{
public:
	void	Init()						override;
	void	Update(Entity* entity, float deltaTime)	override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:
	//float	m_elapsedTime;
};