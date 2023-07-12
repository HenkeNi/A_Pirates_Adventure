#include "Pch.h"
#include "CombatSystem.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include "Core/CoreComponents.h"
#include "EntityManager.h"

#include "Stats/StatsComponents.h"


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

	std::vector<Entity*> entitiesToRemove;

	auto attackers = m_entityManager->FindAllWithComponents<AttackColliderComponent, TransformComponent>();

	for (auto* attacker : attackers)
	{
		auto* attackCollider = attacker->GetComponent<AttackColliderComponent>();	// rename attackCollider?!

		if (!attackCollider->m_isEnabled)
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
			if (Hi_Engine::Physics::Intersects(attackCollider->m_collider, hitbox->m_collider))
			{
				PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityAttacked, std::tuple{ attacker, victim } }); // Don't send event??

				unsigned damage = GetDamageOutput(attacker);
				if (ApplyDamageOutput(victim, damage))
				{
					entitiesToRemove.push_back(victim);
				}
			}
		}
	}

	for (auto* entity : entitiesToRemove)
	{
		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDied, entity });
		m_entityManager->Destroy(entity->GetID());
	}
}

unsigned CombatSystem::GetDamageOutput(Entity* anEntity) const
{ 
	// get weapon component?, check stats (attack, etc)
	return 10;
}

bool CombatSystem::ApplyDamageOutput(Entity* anEntity, unsigned aDamage)
{
	auto* healthComponent = anEntity->GetComponent<HealthComponent>();
	// Get stats, like defence, etc

	healthComponent->m_currentValue -= aDamage;

	return healthComponent->m_currentValue <= 0;
}