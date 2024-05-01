#include "Pch.h"
#include "MoveCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


MoveCommand::MoveCommand()
{
}

MoveCommand::MoveCommand(const FVector2& direction)
	: m_direction{ direction }
{
}

void MoveCommand::Execute(Entity* entity)			
{
	if (!entity)
		return;

	if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Velocity.x = m_direction.x == 0.f ? velocityComponent->Velocity.x : m_direction.x;
		velocityComponent->Velocity.y = m_direction.y == 0.f ? velocityComponent->Velocity.y : m_direction.y;
	}
}

bool MoveCommand::CanPerform(Entity* entity) const
{
	if (!entity)
		return false;

	if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{

	}

	return true;
}