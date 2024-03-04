#include "Pch.h"
#include "SpawnSystem.h"
#include "Entities/EntityManager.h"

SpawnSystem::SpawnSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityDied, this);
}

SpawnSystem::~SpawnSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDied,	this);

	// Listen to chest opened, etc...
}

void SpawnSystem::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() == eMessage::EntityDestroyed)
	{
		auto* entity = std::any_cast<Entity*>(aMsg.GetData());
		Spawn(entity);
	}
}

void SpawnSystem::Update(float aDeltaTime)
{
	// get entieis with spawn components... (check what should be spawned )
}

void SpawnSystem::Spawn(Entity* aSpawner)
{
	if (!aSpawner)
		return;

	auto* transformComponent = aSpawner->GetComponent<TransformComponent>();
	auto currentPosition = transformComponent->CurrentPos;

	if (auto* spawnComponent = aSpawner->GetComponent<SpawnComponent>())
	{
		for (int i = 0; i < spawnComponent->Amount; ++i)
		{
			auto* entity = m_entityManager->Create(spawnComponent->Spawned);
			transformComponent = entity->GetComponent<TransformComponent>();
			transformComponent->CurrentPos = currentPosition;

			PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
		}
	}
}