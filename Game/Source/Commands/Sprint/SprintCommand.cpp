#include "Pch.h"
#include "SprintCommand.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"


SprintCommand::SprintCommand()
	: m_stateComponent{ nullptr }, m_velocityComponent{ nullptr }
{
}

void SprintCommand::Execute()
{
	if (!m_stateComponent || !m_velocityComponent)
		return;

	m_stateComponent->IsRunning = true;
	m_velocityComponent->Speed = 3;
}

void SprintCommand::SetComponent(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent)
{
	m_stateComponent = aStateComponent;
	m_velocityComponent = aVelocityComponent;
}