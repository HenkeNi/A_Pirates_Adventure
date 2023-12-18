#include "Pch.h"
#include "AttackCommand.h"
#include "Components/Combat/CombatComponents.h"
#include "Components/Character/AttributeComponents.h"
#include "Components/Rendering/RenderComponents.h"


AttackCommand::AttackCommand()
	: m_attackComponent{ nullptr }, m_stateComponent{ nullptr }, m_rectComponent{ nullptr }
{
}

void AttackCommand::Execute()
{
	if (!m_attackComponent || !m_stateComponent || !m_rectComponent)
		return;

	if (m_stateComponent->IsAttacking)
		return;

	m_stateComponent->IsAttacking = true;
	m_attackComponent->IsEnabled = true;
	m_rectComponent->Color = { 0.f, 1.0f, 0.f, 1.f }; // Do in Primitive systtem
}

void AttackCommand::SetComponent(AttackComponent* anAttackComponent, CharacterStateComponent* aStateComponent, DebugRectComponent* aRectComponent)
{
	m_attackComponent = anAttackComponent;
	m_stateComponent  = aStateComponent;
	m_rectComponent   = aRectComponent;
}