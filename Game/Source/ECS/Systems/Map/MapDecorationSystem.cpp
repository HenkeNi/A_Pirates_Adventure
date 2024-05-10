#include "Pch.h"
#include "MapDecorationSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Constants.h"

unsigned GetResourceSpawnChance(const std::string& resource); // FIX!

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

void MapDecorationSystem::Receive(Message& message)
{

	// map chunk generated

	auto mapChunk = std::any_cast<Entity*>(message.GetData());

	GenerateResources(mapChunk);
	// PopulateWithFoilage(mapChunk);
}

void MapDecorationSystem::Update(float deltaTime)
{
}

// TODO; redo...
void MapDecorationSystem::GenerateResources(Entity* entity)
{
	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();
	auto* transformComponent = entity->GetComponent<TransformComponent>();

	auto position = transformComponent->CurrentPos;

	for (const auto& tile : mapChunkComponent->Tiles)
	{
		Entity* entity = nullptr;

		// Check if enviroenment component contains tile??? how to store for each enico

		float random = Hi_Engine::GenerateRandomInteger<unsigned>(0, 100);

		if (tile.Type == eTile::Grass)
		{
			if (random < GetResourceSpawnChance("Grass"))
			{
				entity = m_entityManager->Create("grass");
			}
			else if (random < GetResourceSpawnChance("PalmTree"))
			{
				entity = m_entityManager->Create("palm_tree");
			}
		}
		else if (tile.Type == eTile::Sand)
		{
			if (random < GetResourceSpawnChance("PalmTree"))
			{
				entity = m_entityManager->Create("palm_tree");

			}
			else if (random < GetResourceSpawnChance("Rock"))
			{
				entity = m_entityManager->Create("rock");
			}
		}

		if (entity)
		{
			entity->GetComponent<TransformComponent>()->CurrentPos = { position.x + (tile.Coordinates.x * Tile::Size), position.y + (tile.Coordinates.y * Tile::Size) };;
			PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
		}

	}
}

void MapDecorationSystem::PopulateWithFoilage(const Entity* mapChunk)
{
	auto generateFoilage = [&](const std::string& type, unsigned amount, const Entity* mapChunk)
		{
			static const float tileSize = 1.f;

			auto* mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();
			auto* mapTransformComponent = mapChunk->GetComponent<TransformComponent>();

			auto chunkPosition = mapTransformComponent->CurrentPos;
			auto endPosition = FVector2{ chunkPosition.x + Constants::MapChunkLength * tileSize, chunkPosition.y + Constants::MapChunkLength * tileSize };
			//auto endPosition = CU::Vector2<float>{ chunkPosition.x + mapChunkComponent->Width * tileSize, chunkPosition.y + mapChunkComponent->Height * tileSize };

			for (unsigned i = 0; i < amount; ++i)
			{
				auto* entity = m_entityManager->Create(type);
				auto* transform = entity->GetComponent<TransformComponent>();

				//auto sizet = entity->GetComponent<SpriteComponent>()->Subtexture->GetSize(); // TEMP..

				FVector2 position = {
					Hi_Engine::GenerateRandomFloatingPoint<float>(chunkPosition.x + 1.f, endPosition.x - 1.f),
					Hi_Engine::GenerateRandomFloatingPoint<float>(chunkPosition.y + 1.f, endPosition.y - 1.f) };
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




	generateFoilage("PalmTree", 1, mapChunk);
	//generateFoilage("PalmTree", 2, mapChunk);
	generateFoilage("Grass", 7, mapChunk);
	generateFoilage("Rock", 1, mapChunk);

	//static int count = 0;

	//if ((count++) % 5 == 0)
	//	generateFoilage("SkeletonSpawner", 1, mapChunk);
}

unsigned GetResourceSpawnChance(const std::string& resource)
{
	const std::unordered_map<std::string, unsigned> resourceSpawnChance = {
		{ "PalmTree", 20 },
		{ "Rock", 5 },
		{ "Grass", 30 }
	};

	return resourceSpawnChance.at(resource);
}