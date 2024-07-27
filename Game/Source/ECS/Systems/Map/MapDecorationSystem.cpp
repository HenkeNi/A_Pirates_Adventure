#include "Pch.h"
#include "MapDecorationSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Constants.h"
#include "ECS.h"

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
	auto mapChunk = std::any_cast<Entity>(message.GetData());

	GenerateResources(mapChunk);
	// PopulateWithFoilage(mapChunk);
}

void MapDecorationSystem::Update(float deltaTime)
{
}

void MapDecorationSystem::SetSignature()
{
}

// TODO; redo...
void MapDecorationSystem::GenerateResources(Entity entity)
{
	auto* mapChunkComponent = m_ecs->GetComponent<MapChunkComponent>(entity);
	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);


	for (const auto& tile : mapChunkComponent->Tiles) // FIX this !!! 
	{
		Entity spawnedResource;

		bool hasSpawned = false;

		if (tile.Type == eTile::Grass)
		{
			static std::array<std::string, 3> types{
				"Empty",
				"Grass",
				"BerryBush"
			};

			int index = Hi_Engine::GetWeightedRandomIndex({ 0.7f, 0.2f, 0.1f });
			std::string type = types[index];
			if (type != "Empty")
			{
				spawnedResource = m_ecs->CreateEntity(type.c_str());
				hasSpawned = true;
			}
		}
		else if (tile.Type == eTile::Sand)
		{
			static std::array<std::string, 3> types{
				"Empty",
				"PalmTree",
				"Rock"
			};

			int index = Hi_Engine::GetWeightedRandomIndex({ 0.65f, 0.25f, 0.1f });
			std::string type = types[index];
			if (type != "Empty")
			{
				spawnedResource = m_ecs->CreateEntity(type.c_str());
				hasSpawned = true;
			}
		}

		if (hasSpawned)
		{
			auto position = transformComponent->CurrentPos;
			
			m_ecs->GetComponent<TransformComponent>(spawnedResource)->CurrentPos = { position.x + (tile.Coordinates.x * Tile::Size), position.y + (tile.Coordinates.y * Tile::Size) };;
			PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, spawnedResource });
		}

	}
}

void MapDecorationSystem::PopulateWithFoilage(Entity mapChunk)
{
	auto generateFoilage = [&](const std::string& type, unsigned amount, Entity mapChunk)
		{
			static const float tileSize = 1.f;

			auto* mapChunkComponent = m_ecs->GetComponent<MapChunkComponent>(mapChunk);
			auto* mapTransformComponent = m_ecs->GetComponent<TransformComponent>(mapChunk);

			auto chunkPosition = mapTransformComponent->CurrentPos;
			auto endPosition = FVector2{ chunkPosition.x + Constants::MapChunkLength * tileSize, chunkPosition.y + Constants::MapChunkLength * tileSize };
			//auto endPosition = CU::Vector2<float>{ chunkPosition.x + mapChunkComponent->Width * tileSize, chunkPosition.y + mapChunkComponent->Height * tileSize };

			for (unsigned i = 0; i < amount; ++i)
			{
				Entity entity = m_ecs->CreateEntity(type.c_str());
				auto* transform = m_ecs->GetComponent<TransformComponent>(entity);

				//auto sizet = entity->GetComponent<SpriteComponent>()->Subtexture->GetSize(); // TEMP..

				FVector2 position = {
					Hi_Engine::GenerateRandomFloatingPoint<float>(chunkPosition.x + 1.f, endPosition.x - 1.f),
					Hi_Engine::GenerateRandomFloatingPoint<float>(chunkPosition.y + 1.f, endPosition.y - 1.f) };
				transform->CurrentPos = transform->PreviousPos = position;

				if (i % 2 == 0)
					transform->Scale.x *= -1.f;

				//transform->m_scale = { 0.75f, 0.75f, 0.75f };														// should be read from json...

				//auto rect = entity->GetComponent<RectComponent>();
				//rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource("Primitive");

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
	generateFoilage("BerryBush", 3, mapChunk);

	//static int count = 0;

	//if ((count++) % 5 == 0)
	//	generateFoilage("SkeletonSpawner", 1, mapChunk);
}