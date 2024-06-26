#include "Pch.h"
#include "CombatSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Systems/Physics/MovementSystem.h"


CombatSystem::CombatSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::AttackAnimationFinished, this);
	//PostMaster::GetInstance().Subscribe(eMessage::EnemyAttacked, this);
}

CombatSystem::~CombatSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::AttackAnimationFinished, this);
	//PostMaster::GetInstance().Unsubscribe(eMessage::EnemyAttacked, this);
}

void CombatSystem::Receive(Message& message)	// Listen to collisions from physics
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	if (message.GetMessageType() == eMessage::AttackAnimationFinished)
	{
		auto* entity = std::any_cast<Entity*>(message.GetData());
		PerformAttack(entity);
		// call ApplyKnockback here instead?
	}


	// TEmp
	/*if (message.GetMessageType() == eMessage::EnemyAttacked)
	{
		auto* entity = std::any_cast<Entity*>(message.GetData());
		PerformAttack(entity);
	}*/


	
	

	// No need to check if having weapon equipped?


	// TODO; static function in Equipment system to get certain equipments?

	


	// Check if collider with attack is colliding someting with health?




	// activate collider =>





	// Listen for animation finished => activate collider

	// Listen for collision (from physics system)


	// TODO: check if character state "isAiming" is active


	//std::vector<Entity*> entitiesToRemove;

	// auto entity = std::any_cast<Entity*>(aMsg.GetData());
	//auto* attackCollider = entity->GetComponent<AttackComponent>();

	// necessary, or do earlier?
	//if (!attackCollider->m_isEnabled)
		//return;

	//auto targets = GetNearbyEntities();
	//	
	//for (auto target : targets)
	//{
	//	if (target->GetID() == entity->GetID())
	//		continue;

	//	auto hitbox = target->GetComponent<HitboxComponent>();

	//	// if colliding... (move to COllisionSystem)
	//	if (Hi_Engine::Physics::Intersects(attackCollider->Collider, hitbox->Collider))
	//	{
	//		//PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityAttacked, std::tuple{ attacker, target } }); // Don't send event??
	//		PostMaster::GetInstance().SendMessage({ eMessage::EntityAttacked, target });

	//		unsigned damage = GetDamageOutput(entity);
	//		if (ApplyDamageOutput(target, damage))
	//		{
	//			entitiesToRemove.push_back(target);
	//		}
	//	}
	//}
	
	//entity->GetComponent<CharacterStateComponent>()->IsAttacking = false;

	//for (auto* entity : entitiesToRemove)
	//{
	//	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDied, entity });
	//	m_entityManager->Destroy(entity->GetID());
	//}

}

void CombatSystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<HealthComponent>();

	std::vector<unsigned> entitiesToRemove;

	for (auto* entity : entities)
	{
		auto* healthComponent = entity->GetComponent<HealthComponent>();
		if (healthComponent->CurrentValue == 0)
		{
			PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDied, entity });
			entitiesToRemove.push_back(entity->GetID());
		}
	}

	for (auto entity : entitiesToRemove)
		m_entityManager->Destroy(entity);

	//std::vector<Entity*> entitiesToRemove;

	//auto attackers = m_entityManager->FindAll<AttackComponent, TransformComponent>();

	//for (auto* attacker : attackers)
	//{
	//	auto* attackCollider = attacker->GetComponent<AttackComponent>();
	//	
	//	if (!attackCollider->m_isEnabled || !IsCorrectAnimationFrame(attacker))	// TODO; listen to animation event instead?
	//		continue;

	//	// Update color??

	//	// Todo; filter for entities in nearby area!!
	//	auto targets = m_entityManager->FindAll<HealthComponent, HitboxComponent, TransformComponent>();

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

std::vector<Entity*> CombatSystem::GetAdversaries(const Entity* entity)
{
	std::vector<Entity*> adversaries; 

	if (entity)
	{
		// m_entityManager->
	}

	return adversaries;
}

void CombatSystem::PerformAttack(Entity* entity)
{
	auto* equipmentComponent = entity->GetComponent<EquipmentComponent>(); // why?
	if (!equipmentComponent)
		return;

	int weaponID = equipmentComponent->EquippedItemIDs[(int)eEquipmentSlot::Melee];

	if (auto* weapon = m_entityManager->Find(weaponID))
	{
		auto* colliderComponent = weapon->GetComponent<ColliderComponent>();
		auto* weaponComponent = weapon->GetComponent<WeaponComponent>();
		int damageOutput = weaponComponent->DamageDealt;

		PostMaster::GetInstance().SendMessage({ eMessage::ItemUsed, weapon }); // Send weapon swung instead??

		for (const auto& target : colliderComponent->CollidingEntities)
		{
			if (target->GetID() == entity->GetID() || !IsTargetable(target))
				continue;

			// TODO: calculate damage output

			if (target->HasComponent<KnockbackComponent>() && !MovementSystem::IsKnockbacked(target))
			{
				ApplyKnockback(entity, target);
			}

			// HERE??
			PostMaster::GetInstance().SendMessage({ eMessage::EntityAttacked, target });

			auto* healthComponent = target->GetComponent<HealthComponent>();
			healthComponent->CurrentValue = Hi_Engine::Math::Clamp(healthComponent->CurrentValue - damageOutput, 0, healthComponent->MaxHealth);

			// store entities to remoev in entity manager?
		}
	}

}

bool CombatSystem::IsTargetable(Entity* entity) const
{
	if (!entity)
		return false;

	if (auto* healthComponent = entity->GetComponent<HealthComponent>())
	{
		return !healthComponent->IsInvincible;
	}

	return false;
}

unsigned CombatSystem::GetDamageOutput(Entity* entity) const
{ 
	// get attack component
	// 
	// get weapon component?, check stats (attack, etc)
	return 10;
}

//std::vector<Entity*> CombatSystem::GetNearbyEntities() const
//{
//	// Todo; filter for entities in nearby area!!
//	auto targets = m_entityManager->FindAll<HealthComponent, HitboxComponent, TransformComponent>();
//	return targets;
//}

bool CombatSystem::ApplyDamageOutput(Entity* entity, unsigned damage)
{
	auto* healthComponent = entity->GetComponent<HealthComponent>();
	// Get stats, like defence, etc

	healthComponent->CurrentValue -= damage;

	// CurrentHeatValue = std::max(CurrentHeatValue - Amount, 0.f);


	return healthComponent->CurrentValue <= 0;
}

void CombatSystem::ApplyKnockback(Entity* source, Entity* target)
{
	auto* knockbackComponent = target->GetComponent<KnockbackComponent>();
	
	if (MovementSystem::IsKnockbacked(target))
		return;

	auto* transformComponent = source->GetComponent<TransformComponent>();
	auto sourcePosition = transformComponent->CurrentPos;

	transformComponent = target->GetComponent<TransformComponent>();
	auto targetPosition = transformComponent->CurrentPos;


	knockbackComponent->Direction = targetPosition - sourcePosition;
	knockbackComponent->Direction.Normalize();

	knockbackComponent->Power = 2.5f;
	knockbackComponent->Timestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
	knockbackComponent->Duration = 0.25f;

	// TODO; update character state
}
