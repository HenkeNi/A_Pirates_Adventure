#include "Pch.h"
#include "CombatSystem.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include "Core/CoreComponents.h"
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

	//auto entities = m_entityManager->FindAllWithComponents<BoxColliderComponent>();
	auto entities = m_entityManager->FindAllWithComponents<AttackColliderComponent, TransformComponent>();

	for (auto* entity : entities)
	{
		auto* attackComponent = entity->GetComponent<AttackColliderComponent>();

		if (attackComponent->m_isEnabled)
		{
			// Update color??
		}
	}
}
