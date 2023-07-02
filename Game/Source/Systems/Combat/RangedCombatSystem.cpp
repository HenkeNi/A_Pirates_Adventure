#include "Pch.h"
#include "RangedCombatSystem.h"

RangedCombatSystem::RangedCombatSystem()
{
}

RangedCombatSystem::~RangedCombatSystem()
{
}

void RangedCombatSystem::Receive(Message& aMsg)
{
}

void RangedCombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;
}
