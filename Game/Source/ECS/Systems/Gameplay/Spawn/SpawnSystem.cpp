#include "Pch.h"
#include "SpawnSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Utility/UtilityComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


SpawnSystem::SpawnSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
	//PostMaster::GetInstance().Subscribe(eMessage::EntityDied, this);
}

SpawnSystem::~SpawnSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
	//PostMaster::GetInstance().Unsubscribe(eMessage::EntityDied,	this);

	// Listen to chest opened, etc...
}

void SpawnSystem::Receive(Message& message)
{
	auto entity = std::any_cast<Entity>(message.GetData());

	if (m_ecs->HasComponent<SpawnComponent>(entity))
		Spawn(entity);
}

void SpawnSystem::Update(float deltaTime)
{
	// get entieis with spawn components... (check what should be spawned )
}

void SpawnSystem::SetSignature()
{
}

void SpawnSystem::Spawn(Entity spawner)
{
	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(spawner);
	auto position = transformComponent->CurrentPos;

	auto* spawnComponent = m_ecs->GetComponent<SpawnComponent>(spawner);
	
	float spawnRadius = spawnComponent->SpawnRadius;

	for (int i = 0; i < spawnComponent->Amount; ++i)
	{
		auto entity = m_ecs->CreateEntity(spawnComponent->Spawned.c_str(), false);
		
		float xOffset = Hi_Engine::GenerateRandomFloatingPoint(-spawnRadius, spawnRadius);
		float yOffset = Hi_Engine::GenerateRandomFloatingPoint(-spawnRadius, spawnRadius);
		
		transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		transformComponent->CurrentPos = { position.x + xOffset, position.y + yOffset };

		// Add an velocity component? rather than set position, use new position to calc velocity?!

		auto* collectableComponent = m_ecs->GetComponent<CollectableComponent>(entity);
		collectableComponent->SpawnTimestamp = Hi_Engine::Engine::GetTimer().GetTotalTime();
		collectableComponent->PickupDelay = 0.5f; // TODO; do in initialize component!
		
		PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });
	}
}