#include "Pch.h"
#include "SprintCommand.h"
#include "Character/AttributeComponents.h"
#include "Physics/PhysicsComponents.h"


SprintCommand::SprintCommand()
	: m_stateComponent{ nullptr }, m_velocityComponent{ nullptr }
{
}

void SprintCommand::Execute()
{
	if (!m_stateComponent || !m_velocityComponent)
		return;

	m_stateComponent->m_isRunning = true;
	m_velocityComponent->m_speed = 3;
}

void SprintCommand::SetComponent(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent)
{
	m_stateComponent = aStateComponent;
	m_velocityComponent = aVelocityComponent;
}