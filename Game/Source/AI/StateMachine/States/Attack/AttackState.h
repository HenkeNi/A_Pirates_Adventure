#pragma once
#include "../Base/State.h"

class AttackState : public State
{
public:
	void	Init()										override;
	void	Update(Entity* anEntity, float aDeltaTime)	override;

	void	OnEnter()									override;
	void	OnExit()									override;

private:

};