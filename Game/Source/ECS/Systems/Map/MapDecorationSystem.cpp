#include "Pch.h"
#include "MapDecorationSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

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


	PopulateWithFoilage(mapChunk);
}

void MapDecorationSystem::Update(float aDeltaTime)
{
}

void MapDecorationSystem::PopulateWithFoilage(const Entity* aMapChunk)
{
	auto generateFoilage = [&](const std::string& aType, unsigned anAmount, const Entity* aMapChunk)
	{
		static const float tileSize = 1.f;

		auto* mapChunkComponent		= aMapChunk->GetComponent<MapChunkComponent>();
		auto* mapTransformComponent	= aMapChunk->GetComponent<TransformComponent>();

		auto chunkPosition = mapTransformComponent->CurrentPos;
		auto endPosition = CU::Vector2<float>{ chunkPosition.x + mapChunkComponent->Width * tileSize, chunkPosition.y + mapChunkComponent->Height * tileSize };


		for (int i = 0; i < anAmount; ++i)
		{
			auto* entity = m_entityManager->Create(aType);
			auto* transform = entity->GetComponent<TransformComponent>();

			auto sizet = entity->GetComponent<SpriteComponent>()->Subtexture->GetSize(); // TEMP..

			CU::Vector2<float> position = { (float)Random::InRange(chunkPosition.x + 1.f, endPosition.x - 1.f), (float)Random::InRange(chunkPosition.y + 1.f, endPosition.y - 1.f) };
			transform->CurrentPos = transform->PreviousPos = position;

			if (i % 2 == 0)
				transform->Scale.x *= -1.f;

			//transform->m_scale = { 0.75f, 0.75f, 0.75f };														// should be read from json...

			//auto rect = entity->GetComponent<RectComponent>();
			//rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");

			// Fix somehow => need to work even if not moving
			auto hitbox = entity->GetComponent<HitboxComponent>();

			static float size = 0.2f;

			hitbox->Collider.Init({ position.x - size, position.y - size }, { position.x + size, position.y + size });
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