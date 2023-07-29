#include "Pch.h"
#include "MoveCommand.h"
#include "EntityManager.h"


MoveCommand::MoveCommand()
	: m_velocityComponent{ nullptr }, m_direction{ 0.f, 0.f }
{
}

MoveCommand::MoveCommand(const CU::Vector2<float>& aDirection)
	: m_velocityComponent{ nullptr }, m_direction{ aDirection }
{
}

void MoveCommand::SetComponents(VelocityComponent* aVelocityComponent, CharacterStateComponent* aStateComponent)
{
	m_velocityComponent = aVelocityComponent;
	m_characterStateComponent = aStateComponent;
}

void MoveCommand::Execute()
{
	if (!m_velocityComponent || !m_characterStateComponent)
		return;

	// FIX!
	m_velocityComponent->m_velocity.x = m_direction.x == 0.f ? m_velocityComponent->m_velocity.x : m_direction.x;
	m_velocityComponent->m_velocity.z = m_direction.y == 0.f ? m_velocityComponent->m_velocity.z : m_direction.y;

	//m_velocityComponent->m_velocity.x = m_direction.x; // Do += (clamp later)?!
	//m_velocityComponent->m_velocity.z = m_direction.y;

	m_characterStateComponent->m_isWalking = true;
	m_characterStateComponent->m_isIdle = false;

	// if (auto* target = ) -> need an entitymanager!

	// static int x = 20;
	// x += 20;
}

MoveCommand* MoveCommand::Clone() const
{
	return nullptr;
}