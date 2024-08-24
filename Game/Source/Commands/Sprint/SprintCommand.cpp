#include "Pch.h"
#include "SprintCommand.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


SprintCommand::SprintCommand(ECS& ecs)
	: Command{ ecs }, m_sprintSpeed{ 300.f }
{
}

void SprintCommand::Execute(Entity entity)
{
	if (!entity)
		return;
	
	if (auto* velocityComponent = m_ecs.GetComponent<VelocityComponent>(entity))
	{
		velocityComponent->Speed = m_sprintSpeed; // modify velocity insetad?
	}
}

bool SprintCommand::CanPerform(Entity entity) const
{
	if (!entity)
		return false;

	return true;
}

void SprintCommand::Undo(Entity entity)
{
	if (!entity)
		return;

	if (auto* velocityComponent = m_ecs.GetComponent<VelocityComponent>(entity))
	{
		velocityComponent->Speed = 200.f;
	}
}