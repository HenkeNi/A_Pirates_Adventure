#pragma once
#include "../Base/Command.h"

class CharacterStateComponent;
class VelocityComponent;

class SprintCommand : public Command
{
public:
	SprintCommand();

	void			Execute()		  override;

	void			SetComponent(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent);

private:
	CharacterStateComponent* m_stateComponent;
	VelocityComponent*		 m_velocityComponent;
};