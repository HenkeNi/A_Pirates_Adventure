#pragma once
#include "../Base/Command.h"

class AttackColliderComponent;
class CharacterStateComponent;
class DebugRectComponent; // REMOVE LATER...

class AttackCommand : public Command
{
public:
	AttackCommand();

	void			Execute()		  override;

	void			SetComponent(AttackColliderComponent* anAttackComponent, CharacterStateComponent* aStateComponent, DebugRectComponent* aRectComponent);

private:
	AttackColliderComponent* m_attackComponent;
	CharacterStateComponent* m_stateComponent;
	DebugRectComponent* m_rectComponent;
};