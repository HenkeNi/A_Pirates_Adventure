#include "Pch.h"
#include "MeleeCombatSystem.h"


MeleeCombatSystem::MeleeCombatSystem()
{
}

MeleeCombatSystem::~MeleeCombatSystem()
{
}

void MeleeCombatSystem::Receive(Message& message)
{
}

void MeleeCombatSystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;
}
