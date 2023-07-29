#include "Pch.h"
#include "AttackCommand.h"
#include "Combat/CombatComponents.h"
#include "Character/AttributeComponents.h"
#include "Rendering/RenderComponents.h"


AttackCommand::AttackCommand()
	: m_attackComponent{ nullptr }, m_stateComponent{ nullptr }, m_rectComponent{ nullptr }
{
}

void AttackCommand::Execute()
{
	if (!m_attackComponent || !m_stateComponent || !m_rectComponent)
		return;

	if (m_stateComponent->m_isAttacking)
		return;

	m_stateComponent->m_isAttacking = true;
	m_attackComponent->m_isEnabled = true;
	m_rectComponent->m_color = { 0.f, 1.0f, 0.f, 1.f }; // Do in Primitive systtem
}

void AttackCommand::SetComponent(AttackColliderComponent* anAttackComponent, CharacterStateComponent* aStateComponent, DebugRectComponent* aRectComponent)
{
	m_attackComponent = anAttackComponent;
	m_stateComponent  = aStateComponent;
	m_rectComponent   = aRectComponent;
}