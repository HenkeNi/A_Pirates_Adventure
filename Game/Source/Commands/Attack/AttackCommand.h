#pragma once
#include "../Base/Command.h"

struct AttackComponent;
struct CharacterStateComponent;
struct DebugRectComponent; // REMOVE LATER...

class AttackCommand : public Command
{
public:
	AttackCommand();

	void			Execute()		  override;

	void			SetComponent(AttackComponent* anAttackComponent, CharacterStateComponent* aStateComponent, DebugRectComponent* aRectComponent);

private:
	AttackComponent* m_attackComponent;
	CharacterStateComponent* m_stateComponent;
	DebugRectComponent* m_rectComponent;
};