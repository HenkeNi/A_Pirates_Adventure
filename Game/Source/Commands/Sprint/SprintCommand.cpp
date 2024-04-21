#include "Pch.h"
#include "SprintCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"


SprintCommand::SprintCommand()
	: m_sprintSpeed{ 3.f }
{
}

void SprintCommand::Execute(Entity* entity)
{
	if (!entity)
		return;
	
	if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Speed = m_sprintSpeed;
	}
}

bool SprintCommand::CanPerform(Entity* entity) const
{
	if (!entity)
		return false;

	return true;
}

void SprintCommand::Undo(Entity* entity)
{
	if (!entity)
		return;

	if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Speed = 1.f;
	}
}