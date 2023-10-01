#include "Pch.h"
#include "MapGenerationSystem.h"
#include "EntityManager.h"
#include "../Data/Constants.h"
#include "../Utility/Map/MapUtils.h"


MapGenerationSystem::MapGenerationSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this); // NewGameCreated instead?	
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
	// get player position? if left area, make more chunks...

	// auto player = m_entityManager->FindAllWithComponents<PlayerControllerComponent>()[0];
	// auto playerTransformComponent = player->GetComponent<TransformComponent>();


	// auto mapChunks = m_entityManager->FindAllWithComponents<MapChunkComponent>();

	auto players = m_entityManager->FindAllWithComponents<PlayerControllerComponent>();

	if (players.empty())
		return;

	auto player = players[0];
	auto playerPosition = player->GetComponent<TransformComponent>()->m_currentPos;			// Todo, check all 4 corners of player (Get hitboxCollider)

	auto* mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAllWithComponents<MapChunkComponent>(), { playerPosition.x, playerPosition.z });

	//if (mapChunk)
		//std::cout << "Map chunk coordinate: " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.x << ", " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.y << '\n';
}

void MapGenerationSystem::GenerateStartArea()
{
	static const float tileSize = 1.f;

	unsigned size = Constants::g_initialChunkSquareSize;

	for (int col = 0; col < size; ++col)
	{
		for (int row = 0; row < size; ++row)
		{
			bool isLand = col > 0 && col < 4 && row < 4 && row > 0;

			// create mapChunk..
			auto entity = m_entityManager->CreateResources("MapChunk");

			auto* mapChunkComponent		= entity->GetComponent<MapChunkComponent>();
			auto* transformComponent	= entity->GetComponent<TransformComponent>();

			transformComponent->m_currentPos = { (float)col * (mapChunkComponent->m_width * tileSize), 0.f, (float)row * (mapChunkComponent->m_height * tileSize) };
			mapChunkComponent->m_coordinates = { col, row };

			// populate with tiles
			for (int height = 0; height < mapChunkComponent->m_height; ++height)
			{
				for (int width = 0; width < mapChunkComponent->m_width; ++width)
				{
					Tile tile;
					tile.m_coordinates = { height, width };
					tile.m_isCollidable = !isLand;
					tile.m_subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(isLand ? "ground_tiles_00" : "ground_tiles_01");
					/*tile.m_material = {
						&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(isLand ? "sand" : "sea"),
						&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("sprite_batch")
					};*/
					
					mapChunkComponent->m_tiles.push_back(tile);
				}
			}

			// TEMP -> populate regardless of water or land...
			if (isLand)
				PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity });
		}
	}
}

void MapGenerationSystem::GenerateMapChunk()
{

}