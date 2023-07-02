#include "Pch.h"
#include "CombatSystem.h"
#include "Physics/PhysicsComponents.h"
#include "EntityManager.h"


CombatSystem::CombatSystem()
{
}

CombatSystem::~CombatSystem()
{
}

void CombatSystem::Receive(Message& aMsg)
{
}

void CombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	// auto entities = m_entityManager->FindAllWithComponents<BoxColliderComponent>();
}
