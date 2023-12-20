#include "Pch.h"
#include "MoveCommand.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"


MoveCommand::MoveCommand()
	: m_velocityComponent{ nullptr }, m_direction{ 0.f, 0.f }
{
}

MoveCommand::MoveCommand(const CU::Vector2<float>& aDirection)
	: m_velocityComponent{ nullptr }, m_direction{ aDirection }
{
}

void MoveCommand::Execute()
{
	if (!m_velocityComponent || !m_characterStateComponent)
		return;

	// FIX!
	m_velocityComponent->Velocity.x = m_direction.x == 0.f ? m_velocityComponent->Velocity.x : m_direction.x;
	m_velocityComponent->Velocity.z = m_direction.y == 0.f ? m_velocityComponent->Velocity.z : m_direction.y;

	//m_velocityComponent->m_velocity.x = m_direction.x; // Do += (clamp later)?!
	//m_velocityComponent->m_velocity.z = m_direction.y;

	m_characterStateComponent->IsWalking = true;
	m_characterStateComponent->IsIdle = false;

	// if (auto* target = ) -> need an entitymanager!

	// static int x = 20;
	// x += 20;
}

void MoveCommand::SetComponents(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent)
{
	m_velocityComponent = aVelocityComponent;
	m_characterStateComponent = aStateComponent;
}