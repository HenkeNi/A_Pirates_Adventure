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

		auto* bullet = m_entityManager->Create("Bullet");

		auto* transformComponent = bullet->GetComponent<TransformComponent>();
		transformComponent->CurrentPos = data.Position;

		auto* velocityComponent = bullet->GetComponent<VelocityComponent>();
		velocityComponent->Velocity = data.Directin;
		velocityComponent->ShouldSlowDown = false; // Do otherway?

		velocityComponent->Speed = data.Speed;
	}

	// listen to entity shoot event?

	//auto* projectile		= m_entityManager->Create("Bullet");
	//auto* velocityComponent = projectile->GetComponent<VelocityComponent>();
	//velocityComponent->Velocity = { 1.f, 0.f };

}

void RangedCombatSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	static float time = 0.f;

	time += aDeltaTime;

	if (time < 5.f)
		return;


	// if life time is to great or distnace to far => remove bullet...

	/*time = 0.f;
	auto* projectile = m_entityManager->Create("Bullet");
	auto* velocityComponent = projectile->GetComponent<VelocityComponent>();
	velocityComponent->Velocity = { 10.f, 0.f };
	velocityComponent->Speed = 2.f;*/
	
	// if aiming => update the cross hairs position? or do in movement systme, or a dedicated crosshair system?

}
