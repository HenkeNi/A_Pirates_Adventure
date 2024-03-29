#include "Pch.h"
#include "MoveCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


MoveCommand::MoveCommand()
{
}

MoveCommand::MoveCommand(const CU::Vector2<float>& aDirection)
	: m_direction{ aDirection }
{
}

void MoveCommand::Execute(Entity* anEntity)			
{
	if (!anEntity)
		return;

	if (auto* velocityComponent = anEntity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Velocity.x = m_direction.x == 0.f ? velocityComponent->Velocity.x : m_direction.x;
		velocityComponent->Velocity.y = m_direction.y == 0.f ? velocityComponent->Velocity.y : m_direction.y;
	}
}

bool MoveCommand::CanPerform(Entity* anEntity) const
{
	if (!anEntity)
		return false;

	if (auto* characterStateComponent = anEntity->GetComponent<CharacterStateComponent>())
	{

	}

	return true;
}