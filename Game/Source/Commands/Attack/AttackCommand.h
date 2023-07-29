#pragma once
#include "../Base/Command.h"

class AttackColliderComponent;
class CharacterStateComponent;
class RectComponent; // REMOVE LATER...

class AttackCommand : public Command
{
public:
	AttackCommand();

	void			SetComponent(AttackColliderComponent* anAttackComponent, CharacterStateComponent* aStateComponent, RectComponent* aRectComponent);

	void			Execute()		  override;
	AttackCommand*	Clone()		const override;

private:
	AttackColliderComponent* m_attackComponent;
	CharacterStateComponent* m_stateComponent;
	RectComponent* m_rectComponent;
};