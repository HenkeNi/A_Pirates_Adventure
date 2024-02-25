#include "Pch.h"
#include "RangedCombatSystem.h"
#include "Entities/EntityManager.h"

RangedCombatSystem::RangedCombatSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityFired, this);
}

RangedCombatSystem::~RangedCombatSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityFired, this);
}

void RangedCombatSystem::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() == eMessage::EntityFired)
	{
		auto data = std::any_cast<ProjectileData>(aMsg.GetData());

		auto* projectile = m_entityManager->Create("Bullet");

		auto* transformComponent = projectile->GetComponent<TransformComponent>();
		transformComponent->CurrentPos = data.Position;

		auto* velocityComponent = projectile->GetComponent<VelocityComponent>();
		velocityComponent->Velocity = data.Directin;
		velocityComponent->ShouldSlowDown = false; // Do otherway?
		velocityComponent->Speed = data.Speed;

		auto* projectileComponent = projectile->GetComponent<ProjectileComponent>();
		projectileComponent->Timestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
	}
}

void RangedCombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;


	auto projectiles = m_entityManager->FindAll<ProjectileComponent>();

	std::vector<Entity*> destroyed;

	double time = Hi_Engine::Engine::GetTimer().GetTotalTime();
	for (auto& projectile : projectiles)
	{
		auto* projectileComponent = projectile->GetComponent<ProjectileComponent>();

		// TODO; replace with a distance check? or check against the bounds of the screen instead? (allowing projectiles to travel until colliding with something, if going same direction as player)
		if (time >= projectileComponent->Timestamp + projectileComponent->LifeTime)
		{
			destroyed.push_back(projectile); // should a system handle this?
		}
	}

	for (auto it = destroyed.rbegin(); it != destroyed.rend(); ++it)
	{
		m_entityManager->Destroy((*it)->GetID());
	}
}