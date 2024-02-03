#include "Pch.h"
#include "SprintCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"


SprintCommand::SprintCommand()
	: m_sprintSpeed{ 3.f }
{
}

void SprintCommand::Execute(Entity* anEntity)
{
	if (!anEntity)
		return;
	
	if (auto* velocityComponent = anEntity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Speed = m_sprintSpeed;
	}
}

bool SprintCommand::CanPerform(Entity* anEntity) const
{
	if (!anEntity)
		return false;

	return true;
}

void SprintCommand::Undo(Entity* anEntity)
{
	if (!anEntity)
		return;

	if (auto* velocityComponent = anEntity->GetComponent<VelocityComponent>())
	{
		velocityComponent->Speed = 1.f;
	}
}