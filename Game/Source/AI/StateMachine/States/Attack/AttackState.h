#pragma once
#include "../Base/State.h"

class AttackState : public State
{
public:
	void	Init()						override;
	void	Update(Entity* entity)		override;

	void	OnEnter()					override;
	void	OnExit()					override;

private:

};