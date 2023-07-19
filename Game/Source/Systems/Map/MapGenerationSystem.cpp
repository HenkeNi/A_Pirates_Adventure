#include "Pch.h"
#include "MapGenerationSystem.h"
#include "EntityManager.h"
#include "../PostMaster/PostMaster.h"


MapGenerationSystem::MapGenerationSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

MapGenerationSystem::~MapGenerationSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void MapGenerationSystem::Receive(Message& aMsg)
{
	GenerateStartArea();
}

void MapGenerationSystem::Update(float aDeltaTime)
{
}

void MapGenerationSystem::GenerateStartArea()
{
	static const float tileSize = 1.f;

	for (int col = 0; col < 5; ++col)
	{
		for (int row = 0; row < 5; ++row)
		{
			bool isLand = col > 0 && col < 4 && row < 4 && row > 0;

			// create mapChunk..
			auto entity = m_entityManager->Create("MapChunk");

			auto* mapChunkComponent		= entity->GetComponent<MapChunkComponent>();
			auto* transformComponent	= entity->GetComponent<TransformComponent>();

			transformComponent->m_currentPos = { (float)col * (mapChunkComponent->m_width * tileSize),  0.f, (float)row * (mapChunkComponent->m_height * tileSize) };

			// populate with tiles

			for (int height = 0; height < mapChunkComponent->m_height; ++height)
			{
				for (int width = 0; width < mapChunkComponent->m_width; ++width)
				{
					Tile tile;
					tile.m_coordinates = { height, width };
					Hi_Engine::Material material{
						&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(isLand ? "sand01" : "sea"),
						&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard")
					};
					tile.m_material = material;

					tile.m_isCollidable = !isLand;

					mapChunkComponent->m_tiles.push_back(tile);
				}
			}

			// TEMP
			if (isLand)
				PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity });
		}
	}
}


//std::vector<MapChunk> MapGenerator::GenerateStartArea()
//{
//
//	// Pass responsibility to Map? 
//	unsigned tileSize = 1.f;
//	std::vector<MapChunk> mapChunks;
//
//	for (int col = 0; col < 5; ++col)
//	{
//		for (int row = 0; row < 5; ++row)
//		{
//			MapChunk chunk{};
//			//chunk.SetPosition({ (float)col + chunk.m_chunkWidth * tileSize, 0.f, (float)row + chunk.m_chunkHeight * tileSize });
//			chunk.SetPosition({ (float)col * (chunk.m_chunkWidth * tileSize),  0.f, (float)row * (chunk.m_chunkHeight * tileSize) });
//
//			bool isLand = (col > 0 && col < 4) && (row > 0 && row < 4);
//			chunk.m_isWater = !isLand;
//			chunk.CreateTiles(isLand);
//
//			mapChunks.push_back(chunk);
//
//			// generate foilage here?
//		}
//	}
//
//	return mapChunks;
//}
