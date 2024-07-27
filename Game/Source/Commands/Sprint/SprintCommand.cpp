#include "Pch.h"
#include "SprintCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


SprintCommand::SprintCommand()
	: m_sprintSpeed{ 300.f }
{
}

void SprintCommand::Execute(Entity entity, ECS& ecs)
{
	if (!entity)
		return;
	
	if (auto* velocityComponent = ecs.GetComponent<VelocityComponent>(entity))
	{
		velocityComponent->Speed = m_sprintSpeed; // modify velocity insetad?
	}
}

bool SprintCommand::CanPerform(Entity entity, ECS& ecs) const
{
	if (!entity)
		return false;

	return true;
}

void SprintCommand::Undo(Entity entity, ECS& ecs)
{
	if (!entity)
		return;

	if (auto* velocityComponent = ecs.GetComponent<VelocityComponent>(entity))
	{
		velocityComponent->Speed = 200.f;
	}
}