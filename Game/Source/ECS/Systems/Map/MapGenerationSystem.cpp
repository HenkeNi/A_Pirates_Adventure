#include "Pch.h"
#include "MapGenerationSystem.h"
#include "Entities/EntityManager.h"
//#include "../Data/Constants.h"
#include "../Utility/Map/MapUtils.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Map/MapComponents.h"



eTile GetTileType(float aNoise)
{
	static const std::unordered_map<eTile, float> noiseRanges = { 
		{ eTile::Grass,			0.4f },
		{ eTile::Sand,			0.2f },
		{ eTile::ShallowWater,	0.f },
		{ eTile::Water,			-0.2f },
		{ eTile::DeepWater,		-0.5f },
	};

	for (const auto& [type, value] : noiseRanges)
	{
		if (aNoise > value)
		{
			return type;
		}
	}

	return eTile::Water;
}

std::string GetSubtexture(eTile aType)
{
	static const std::unordered_map<eTile, std::string> textures = {
		{ eTile::Grass,			"island_tileset_36" },
		{ eTile::Sand,			"island_tileset_13" },
		{ eTile::ShallowWater,  "island_tileset_18" },
		{ eTile::Water,			"ground_tiles_01" },
		{ eTile::DeepWater,		"island_tileset_06" },
	};

	return textures.at(aType);
}


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
	GenerateMapChunk();
}

void MapGenerationSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	return;

	// get player position? if left area, make more chunks...

	// auto player = m_entityManager->FindAll<PlayerControllerComponent>()[0];
	// auto playerTransformComponent = player->GetComponent<TransformComponent>();


	// auto mapChunks = m_entityManager->FindAll<MapChunkComponent>();

	auto players = m_entityManager->FindAll<PlayerControllerComponent>();

	if (players.empty())
		return;

	auto player = players[0];
	auto playerPosition = player->GetComponent<TransformComponent>()->CurrentPos;			// Todo, check all 4 corners of player (Get hitboxCollider)

	auto* mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAll<MapChunkComponent>(), { playerPosition.x, playerPosition.y });

	//if (mapChunk)
		//std::cout << "Map chunk coordinate: " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.x << ", " << mapChunk->GetComponent<MapChunkComponent>()->m_coordinates.y << '\n';
}

void MapGenerationSystem::GenerateMapChunk()
{
	FastNoiseLite fastNoise;
	fastNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	fastNoise.SetFrequency(0.06f);
	//fastNoise.SetFrequency(0.006f);

	static const float tileSize = 1.f;

	unsigned size = Constants::InitialChunkSquareSize;

	// create mapChunk..
	auto entity = m_entityManager->Create("MapChunk");

	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();
	auto* transformComponent = entity->GetComponent<TransformComponent>();

	transformComponent->CurrentPos = { 0, 0 }; //{ (float)col * (mapChunkComponent->Width * tileSize), (float)row * (mapChunkComponent->Height * tileSize) };
	mapChunkComponent->Coordinates = { 0, 0 };// { col, row };

	// populate with tiles
	for (int height = 0; height < mapChunkComponent->Height; ++height)
	{
		for (int width = 0; width < mapChunkComponent->Width; ++width)
		{
			float noise = fastNoise.GetNoise((float)width, float(height));

			Tile tile;
			tile.Coordinates = { height, width };
			tile.IsCollidable = false; // FIX!
			tile.Type = GetTileType(noise);
	
			std::string subtexture = GetSubtexture(tile.Type);
			tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(subtexture); // Sprite sheet is revered??
			mapChunkComponent->Tiles.push_back(tile);

			// Check if more optimized (dont have to do every frame?!)
			Hi_Engine::SpriteRenderData renderData;
			renderData.Color = { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
			renderData.Subtexture = tile.Subtexture;
			auto currentPosition = transformComponent->CurrentPos;

			glm::vec3 position = { currentPosition.x, currentPosition.y, 0.f };
			position.x += tile.Coordinates.x * Tile::Size;
			position.y += tile.Coordinates.y * Tile::Size;
			renderData.Transform = { position, { 1.f, 1.f }, 0.f };
			mapChunkComponent->RenderData.push_back(renderData);
		}
	}

	// TEMP -> populate regardless of water or land...
	//if (isLand)
	PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity });
}