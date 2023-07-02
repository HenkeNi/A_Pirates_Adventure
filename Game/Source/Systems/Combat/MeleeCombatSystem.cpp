#include "Pch.h"
#include "MeleeCombatSystem.h"


MeleeCombatSystem::MeleeCombatSystem()
{
}

MeleeCombatSystem::~MeleeCombatSystem()
{
}

void MeleeCombatSystem::Receive(Message& aMsg)
{
}

void MeleeCombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;
}
