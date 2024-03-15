#include "Pch.h"
#include "MapDecorationSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

unsigned GetResourceSpawnChance(const std::string& aResource); // FIX!

struct ResourceSpawnSettings
{

};


MapDecorationSystem::MapDecorationSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::MapChunkGenerated, this);
}

MapDecorationSystem::~MapDecorationSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::MapChunkGenerated, this);
}

void MapDecorationSystem::Receive(Message& aMsg)
{

	// map chunk generated

	auto mapChunk = std::any_cast<Entity*>(aMsg.GetData());

	GenerateResources(mapChunk);
	// PopulateWithFoilage(mapChunk);
}

void MapDecorationSystem::Update(float aDeltaTime)
{
}

void MapDecorationSystem::GenerateResources(Entity* anEnity)
{
	auto* mapChunkComponent = anEnity->GetComponent<MapChunkComponent>();
	auto* transformComponent = anEnity->GetComponent<TransformComponent>();

	auto position = transformComponent->CurrentPos;

	for (const auto& tile : mapChunkComponent->Tiles)
	{
		Entity* entity = nullptr;

		if (tile.Type == eTile::Grass)
		{

			if (Random::InRange(0, 100) < GetResourceSpawnChance("Grass"))
			{
				entity = m_entityManager->Create("Grass");
			}
			else if (Random::InRange(0, 100) < GetResourceSpawnChance("PalmTree"))
			{
				entity = m_entityManager->Create("PalmTree");
			}
		}
		else if (tile.Type == eTile::Sand)
		{
			if (Random::InRange(0, 100) < GetResourceSpawnChance("PalmTree"))
			{
				entity = m_entityManager->Create("PalmTree");
				entity->GetComponent<TransformComponent>()->Pivot = { 0.f, 0.5f };

			}
			else if (Random::InRange(0, 100) < GetResourceSpawnChance("Rock"))
			{
				entity = m_entityManager->Create("Rock");
			}
		}

		if (entity)
		{
			entity->GetComponent<TransformComponent>()->CurrentPos = { position.x + (tile.Coordinates.x * Tile::Size), position.y + (tile.Coordinates.y * Tile::Size) };;
			PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
		}

	}


}

void MapDecorationSystem::PopulateWithFoilage(const Entity* aMapChunk)
{
	auto generateFoilage = [&](const std::string& aType, unsigned anAmount, const Entity* aMapChunk)
		{
			static const float tileSize = 1.f;

			auto* mapChunkComponent = aMapChunk->GetComponent<MapChunkComponent>();
			auto* mapTransformComponent = aMapChunk->GetComponent<TransformComponent>();

			auto chunkPosition = mapTransformComponent->CurrentPos;
			auto endPosition = CU::Vector2<float>{ chunkPosition.x + MapChunkComponent::TileCountPerSide * tileSize, chunkPosition.y + MapChunkComponent::TileCountPerSide * tileSize };
			//auto endPosition = CU::Vector2<float>{ chunkPosition.x + mapChunkComponent->Width * tileSize, chunkPosition.y + mapChunkComponent->Height * tileSize };

			for (int i = 0; i < anAmount; ++i)
			{
				auto* entity = m_entityManager->Create(aType);
				auto* transform = entity->GetComponent<TransformComponent>();

				//auto sizet = entity->GetComponent<SpriteComponent>()->Subtexture->GetSize(); // TEMP..

				CU::Vector2<float> position = { (float)Random::InRange(chunkPosition.x + 1.f, endPosition.x - 1.f), (float)Random::InRange(chunkPosition.y + 1.f, endPosition.y - 1.f) };
				transform->CurrentPos = transform->PreviousPos = position;

				if (i % 2 == 0)
					transform->Scale.x *= -1.f;

				//transform->m_scale = { 0.75f, 0.75f, 0.75f };														// should be read from json...

				//auto rect = entity->GetComponent<RectComponent>();
				//rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");

				// Fix somehow => need to work even if not moving
				//auto colliderComponent = entity->GetComponent<ColliderComponent>();
				//static float size = 0.2f;
				//colliderComponent->Collider.Init({ position.x - size, position.y - size }, { position.x + size, position.y + size });

				PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
			}
		};

	// Dont generate if water!!




	generateFoilage("PalmTree", 1, aMapChunk);
	//generateFoilage("PalmTree", 2, aMapChunk);
	generateFoilage("Grass", 7, aMapChunk);
	generateFoilage("Rock", 1, aMapChunk);

	//static int count = 0;

	//if ((count++) % 5 == 0)
	//	generateFoilage("SkeletonSpawner", 1, aMapChunk);
}

unsigned GetResourceSpawnChance(const std::string& aResource)
{
	const std::unordered_map<std::string, unsigned> resourceSpawnChance = {
		{ "PalmTree", 20 },
		{ "Rock", 5 },
		{ "Grass", 30 }
	};

	return resourceSpawnChance.at(aResource);
}