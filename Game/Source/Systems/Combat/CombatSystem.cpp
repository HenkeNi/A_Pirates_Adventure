#include "Pch.h"
#include "CombatSystem.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include "Core/CoreComponents.h"
#include "EntityManager.h"

#include "Stats/StatsComponents.h"


CombatSystem::CombatSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::AttackAnimationFinished, this);
}

CombatSystem::~CombatSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::AttackAnimationFinished, this);
}

void CombatSystem::Receive(Message& aMsg)	// Listen to collisions from physics
{
	if (!m_entityManager)
		return;
	


	// Listen for animation finished => activate collider

	// Listen for collision (from physics system)





	std::vector<Entity*> entitiesToRemove;

	auto entity = std::any_cast<Entity*>(aMsg.GetData());
	auto* attackCollider = entity->GetComponent<AttackComponent>();

	// necessary, or do earlier?
	//if (!attackCollider->m_isEnabled)
		//return;

	auto targets = GetNearbyEntities();
		
	for (auto target : targets)
	{
		if (target->GetID() == entity->GetID())
			continue;

		auto hitbox = target->GetComponent<HitboxComponent>();

		// if colliding... (move to COllisionSystem)
		if (Hi_Engine::Physics::Intersects(attackCollider->Collider, hitbox->Collider))
		{
			//PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityAttacked, std::tuple{ attacker, target } }); // Don't send event??

			unsigned damage = GetDamageOutput(entity);
			if (ApplyDamageOutput(target, damage))
			{
				entitiesToRemove.push_back(target);
			}
		}
	}
	
	entity->GetComponent<CharacterStateComponent>()->IsAttacking = false;

	for (auto* entity : entitiesToRemove)
	{
		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDied, entity });
		m_entityManager->Destroy(entity->GetID());
	}

}

void CombatSystem::Update(float aDeltaTime)
{
	//if (!m_entityManager)
	//	return;

	//std::vector<Entity*> entitiesToRemove;

	//auto attackers = m_entityManager->FindAllWithComponents<AttackComponent, TransformComponent>();

	//for (auto* attacker : attackers)
	//{
	//	auto* attackCollider = attacker->GetComponent<AttackComponent>();
	//	
	//	if (!attackCollider->m_isEnabled || !IsCorrectAnimationFrame(attacker))	// TODO; listen to animation event instead?
	//		continue;

	//	// Update color??

	//	// Todo; filter for entities in nearby area!!
	//	auto targets = m_entityManager->FindAllWithComponents<HealthComponent, HitboxComponent, TransformComponent>();

	//	for (auto target : targets)
	//	{
	//		if (target->GetID() == attacker->GetID())
	//			continue;

	//		auto hitbox = target->GetComponent<HitboxComponent>();

	//		// if colliding...
	//		if (Hi_Engine::Physics::Intersects(attackCollider->m_collider, hitbox->m_collider))
	//		{
	//			PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityAttacked, std::tuple{ attacker, target } }); // Don't send event??

	//			unsigned damage = GetDamageOutput(attacker);
	//			if (ApplyDamageOutput(target, damage))
	//			{
	//				entitiesToRemove.push_back(target);
	//			}
	//		}
	//	}
	//}

	//for (auto* entity : entitiesToRemove)
	//{
	//	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDied, entity });
	//	m_entityManager->Destroy(entity->GetID());
	//}
}

unsigned CombatSystem::GetDamageOutput(Entity* anEntity) const
{ 
	// get weapon component?, check stats (attack, etc)
	return 10;
}

std::vector<Entity*> CombatSystem::GetNearbyEntities() const
{
	// Todo; filter for entities in nearby area!!
	auto targets = m_entityManager->FindAllWithComponents<HealthComponent, HitboxComponent, TransformComponent>();
	return targets;
}

bool CombatSystem::ApplyDamageOutput(Entity* anEntity, unsigned aDamage)
{
	auto* healthComponent = anEntity->GetComponent<HealthComponent>();
	// Get stats, like defence, etc

	healthComponent->CurrentValue -= aDamage;

	// CurrentHeatValue = std::max(CurrentHeatValue - Amount, 0.f);


	return healthComponent->CurrentValue <= 0;
}