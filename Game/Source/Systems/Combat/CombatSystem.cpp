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
#include "Stats/StatsComponents.h"
void CombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto attackers = m_entityManager->FindAllWithComponents<AttackColliderComponent, TransformComponent>();

	std::vector<Entity*> tempToRemove;

	for (auto* attacker : attackers)
	{
		auto* attackComponent = attacker->GetComponent<AttackColliderComponent>();

		if (!attackComponent->m_isEnabled)
			continue;

		// Update color??

		// for all with health component (in nearby area)
		auto victims = m_entityManager->FindAllWithComponents<HealthComponent, HitboxColliderComponent, TransformComponent>();

		for (auto victim : victims)
		{
			if (victim->GetID() == attacker->GetID())
				continue;

			auto hitbox = victim->GetComponent<HitboxColliderComponent>();

			// if colliding...
			if (Hi_Engine::Physics::Intersects(attackComponent->m_collider, hitbox->m_collider))
			{
				// Destroy entity

				tempToRemove.push_back(victim); // TEMP!!!
				//m_entityManager->Destroy(victim->GetID()); // Move to a Health/Stats system...

			}
		}
	}





	// temp

	for (auto v : tempToRemove)
		m_entityManager->Destroy(v->GetID());

}
