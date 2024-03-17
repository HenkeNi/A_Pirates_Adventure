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
	auto position = transformComponent->CurrentPos;

	if (auto* spawnComponent = aSpawner->GetComponent<SpawnComponent>())
	{
		for (int i = 0; i < spawnComponent->Amount; ++i)
		{
			auto* entity = m_entityManager->Create(spawnComponent->Spawned);

			float xOffset = CommonUtilities::GetRandomFloat(-0.5f, 0.5f);
			float yOffset = CommonUtilities::GetRandomFloat(-0.5f, 0.5f);

			transformComponent = entity->GetComponent<TransformComponent>();
			transformComponent->CurrentPos = { position.x + xOffset, position.y + yOffset };

			// Add an velocity component? rather than set position, use new position to calc velocity?!

			auto* collectableComponent = entity->GetComponent<CollectableComponent>();
			collectableComponent->SpawnTimestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
			collectableComponent->PickupDelay = 0.5f;

			PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
		}
	}
}