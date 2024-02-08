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

std::string GetSubtexture(eTile aType) // TODO: check neighbours?
{
	static const std::unordered_map<eTile, std::string> textures = {
		{ eTile::Grass,			"island_tileset_36" },
		{ eTile::Sand,			"island_tileset_13" },
		{ eTile::ShallowWater,  "island_tileset_18" },
		{ eTile::Water,			"island_tileset_18" },
		{ eTile::DeepWater,		"island_tileset_18" }, // NEEDED??
	};

	return textures.at(aType);
}

glm::vec4 GetTileColor(eTile aType)
{
	if (aType == eTile::ShallowWater)
		return { 0.25f, 0.88f, 0.81f, 1.f };
	if (aType == eTile::Water)
		return { 0.f, 0.69f, 0.63f, 1.f };
	if (aType == eTile::DeepWater)
		return { 0.f, 0.16f, 0.16f, 1.f };

	return { 1.f, 1.f, 1.f, 1.f };
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
	// Generate x amount of areas...

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			GenerateMapChunk(x, y);
		}
	}
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

void MapGenerationSystem::GenerateMapChunk(int xCoord, int yCoord)
{
	FastNoiseLite fastNoise;
	fastNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	fastNoise.SetFrequency(0.06f);
	//fastNoise.SetFrequency(0.006f);

	// Generate numbers first??

	static const float tileSize = 1.f;

	// FIX; read from component...
	const int width = 10;

	unsigned size = Constants::InitialChunkSquareSize;

	// create mapChunk..
	auto* entity = m_entityManager->Create("MapChunk");

	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();
	auto* transformComponent = entity->GetComponent<TransformComponent>();

	mapChunkComponent->Coordinates = { xCoord, yCoord };// { col, row };
	
	float xPos = xCoord * (width * Tile::Size);
	float yPos = yCoord * (width * Tile::Size);
	transformComponent->CurrentPos = { xPos, yPos }; //{ (float)col * (mapChunkComponent->Width * tileSize), (float)row * (mapChunkComponent->Height * tileSize) };
	
	//transformComponent->CurrentPos = { 0, 0 }; //{ (float)col * (mapChunkComponent->Width * tileSize), (float)row * (mapChunkComponent->Height * tileSize) };
	//mapChunkComponent->Coordinates = { 0, 0 };// { col, row };

	// populate with tiles
	for (int height = 0; height < 10 /*mapChunkComponent->Height*/; ++height)
	{
		for (int width = 0; width < 10 /*mapChunkComponent->Width*/; ++width)
		{
			float noise = fastNoise.GetNoise((float)xPos + (float)width, (float)yPos + float(height));

			Tile tile;
			tile.Coordinates = { height, width };
			tile.IsCollidable = false; // FIX!
			tile.Type = GetTileType(noise);
	
			std::string subtexture = GetSubtexture(tile.Type);
			tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(subtexture); // Sprite sheet is revered??
			mapChunkComponent->Tiles.push_back(tile);

			// Check if more optimized (dont have to do every frame?!)
			Hi_Engine::SpriteRenderData renderData;
			renderData.Color = GetTileColor(tile.Type); // { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
			renderData.Subtexture = tile.Subtexture;
			auto currentPosition = transformComponent->CurrentPos;

			glm::vec3 position = { currentPosition.x, currentPosition.y, 0.f };
			position.x += tile.Coordinates.x * Tile::Size;
			position.y += tile.Coordinates.y * Tile::Size;
			renderData.Transform = { position, { 1.01f, 1.01f }, 0.f }; // TEMP Solution with scale at 1.01f
			mapChunkComponent->RenderData.push_back(renderData);
		}
	}

	//RetileMapChunk(entity); => wont work?! uses render data now more...

	// TEMP -> populate regardless of water or land...
	//if (isLand)
	PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity });
}

void MapGenerationSystem::RetileMapChunk(Entity* anEntity)
{
	auto* mapChunkComponent = anEntity->GetComponent<MapChunkComponent>();
	
	for (int i = 0; i < 100; ++i)
	{
		if (mapChunkComponent->Tiles[i].Type != eTile::Sand)
			continue;

		if (MapUtils::GetTileTypeInDirection(anEntity, i, eDirection::Down) == eTile::ShallowWater)
		{
			auto& tiles = mapChunkComponent->Tiles;
			tiles[i].Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("island_tileset_31");
			tiles[i].Color = { 0.f, 0.3f, 0.5f, 1.f };
			//mapChunkComponent->Tiles.at(i).Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("island_tileset_31");
		}

	}
}