#pragma once
#include "../Base/Command.h"
#include "Utility/Math/Vectors/Vector.hpp"


namespace CU = CommonUtilities;

class VelocityComponent;
class CharacterStateComponent;

class MoveCommand : public Command	// derive from EntityCommand? (GlobalCommand)
{
public:
	MoveCommand();
	MoveCommand(const CU::Vector2<float>& aDirection);

	void			Execute()		  override;

	void			SetComponents(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent);

	//void Execute(GameObject& aGameObject) override;	// do this instead...?? or pass in constructor as member??

private:
	VelocityComponent*			m_velocityComponent;
	CharacterStateComponent*	m_characterStateComponent;
	CU::Vector2<float>			m_direction;
};
