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
	auto playerPosition = player->GetComponent<TransformComponent>()->CurrentPos;			// Todo, check all 4 corners of player (Get hitboxCollider)

	auto* mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAllWithComponents<MapChunkComponent>(), { playerPosition.x, playerPosition.z });

	//if (mapChunk)
		//std::cout << "Map chunk coordinate: " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.x << ", " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.y << '\n';
}

void MapGenerationSystem::GenerateStartArea()
{
	static const float tileSize = 1.f;

	unsigned size = Constants::InitialChunkSquareSize;

	// For each chunk..
	for (int col = 0; col < size; ++col)
	{
		for (int row = 0; row < size; ++row)
		{
			bool isLand = col > 0 && col < 4 && row < 4 && row > 0; 

			bool isGrass = col == 2 && row == 3;

			// create mapChunk..
			auto entity = m_entityManager->CreateResources("MapChunk");

			auto* mapChunkComponent		= entity->GetComponent<MapChunkComponent>();
			auto* transformComponent	= entity->GetComponent<TransformComponent>();

			transformComponent->CurrentPos = { (float)col * (mapChunkComponent->Width * tileSize), 0.f, (float)row * (mapChunkComponent->Height * tileSize) };
			mapChunkComponent->Coordinates = { col, row };

			// populate with tiles
			for (int height = 0; height < mapChunkComponent->Height; ++height)
			{
				for (int width = 0; width < mapChunkComponent->Width; ++width)
				{
					Tile tile;
					tile.Coordinates = { height, width };
					tile.IsCollidable = !isLand;
					tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(isGrass ? "island_tileset_47" : isLand ? "island_tileset_13" : "ground_tiles_01"); // Sprite sheet is revered??
					//tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(isLand ? "ground_tiles_00" : "ground_tiles_01");
					/*tile.m_material = {
						&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(isLand ? "sand" : "sea"),
						&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("sprite_batch")
					};*/
					
					mapChunkComponent->Tiles.push_back(tile);
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