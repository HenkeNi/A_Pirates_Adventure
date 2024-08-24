#include "Pch.h"
#include "MoveCommand.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


MoveCommand::MoveCommand(ECS& ecs)
	: Command{ ecs }
{
}

MoveCommand::MoveCommand(ECS& ecs, const FVector2& direction)
	: Command{ ecs }, m_direction{ direction }
{
}

void MoveCommand::Execute(Entity entity)
{
	if (!entity)
		return;

	if (auto* velocityComponent = m_ecs.GetComponent<VelocityComponent>(entity))
	{
		// send events instead!!!??

		velocityComponent->Velocity.x = m_direction.x == 0.f ? velocityComponent->Velocity.x : m_direction.x;
		velocityComponent->Velocity.y = m_direction.y == 0.f ? velocityComponent->Velocity.y : m_direction.y;
		//velocityComponent->Acceleration.x = (m_direction.x == 0.f) ? velocityComponent->Acceleration.x : m_direction.x;
		//velocityComponent->Acceleration.y = (m_direction.y == 0.f) ? velocityComponent->Acceleration.y : m_direction.y;
	}
}

bool MoveCommand::CanPerform(Entity entity) const
{
	if (!entity)
		return false;

	//if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	//{

	//}

	return true;
}