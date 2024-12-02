#include "Pch.h"
#include "ProjectileSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


ProjectileSystem::ProjectileSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityFired, this);
}

ProjectileSystem::~ProjectileSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityFired, this);
}

void ProjectileSystem::Receive(Message& message)
{
	assert(m_ecs && "[ProjectileSystem - ERROR]: ECS is not initialized!");

	if (message.GetMessageType() == eMessage::EntityFired)
	{
		auto data = std::any_cast<ProjectileData>(message.GetData());


		Entity projectile = m_ecs->CreateEntityFromBlueprint("Bullet");

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(projectile);
		transformComponent->CurrentPos = data.Position;

		auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(projectile);
		velocityComponent->Velocity = data.Directin;
		velocityComponent->IsVelocityConstant = true;
		velocityComponent->CurrentSpeed = data.Speed;

		auto* projectileComponent = m_ecs->GetComponent<ProjectileComponent>(projectile);
		projectileComponent->Timestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
	}
}

void ProjectileSystem::Update(float deltaTime)
{
	assert(m_ecs && "[ProjectileSystem - ERROR]: ECS is not initialized!");

	auto projectiles = m_ecs->FindEntities(m_signatures["Projectiles"]);

	std::vector<Entity> destroyed;

	double time = Hi_Engine::Engine::GetTimer().GetTotalTime();
	for (auto& projectile : projectiles)
	{
		auto* projectileComponent = m_ecs->GetComponent<ProjectileComponent>(projectile);

		// TODO; replace with a distance check? or check against the bounds of the screen instead? (allowing projectiles to travel until colliding with something, if going same direction as player)
		if (time >= projectileComponent->Timestamp + projectileComponent->LifeTime)
		{
			destroyed.push_back(projectile); // should a system handle this?
		}
	}

	for (auto it = destroyed.rbegin(); it != destroyed.rend(); ++it)
	{
		m_ecs->DestroyEntity(*it);
	}
}

void ProjectileSystem::SetSignature()
{
	m_signatures.insert({ "Projectiles", m_ecs->GetSignature<ProjectileComponent>() });
}
