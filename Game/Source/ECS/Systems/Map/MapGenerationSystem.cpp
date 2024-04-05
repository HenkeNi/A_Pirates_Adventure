#include "Pch.h"
#include "MapGenerationSystem.h"
#include "Entities/EntityManager.h"
//#include "../Data/Constants.h"
#include "../Utility/Map/MapUtils.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Map/MapComponents.h"
#include <FastNoiseLite.h>



CU::Vector2<int> ConvertWorldPositionToMapChunkCoordinates(const CU::Vector2<float>& worldPosition)
{
	float chunkSize = MapChunkComponent::TileCountPerSide * Tile::Size;

	CU::Vector2<int> coordinates;
	coordinates.x = (int)std::floor(worldPosition.x / chunkSize);
	coordinates.y = (int)std::floor(worldPosition.y / chunkSize);

	return coordinates;
}


// WHere to store various tile settings? ResourceHolder TileSettings?
struct TileSettings
{
	std::string Identifier; //?? NEEDED?
	CU::Vector4<float> Color;
	// ARray of subtextures??
	bool IsCollidable;
};


eTile GetTileType(float noise)
{
	int noiseValue = (int)(noise * 10);

	// std::cout << noise << "\n";

	static const std::unordered_map<eTile, int> tileHeightValues = {
	{ eTile::Grass,			4 },
	{ eTile::Sand,			2 },
	{ eTile::ShallowWater,	0 },
	{ eTile::Water,			-1 },
	{ eTile::DeepWater,		-3 },
	};

	for (const auto& [type, value] : tileHeightValues)
	{
		if (noiseValue >= value)
		{
			return type;
		}
	}

	return eTile::Water;

	//static const std::unordered_map<eTile, float> noiseRanges = { 
	//	{ eTile::Grass,			0.4f },
	//	{ eTile::Sand,			0.2f },
	//	{ eTile::ShallowWater,	0.f },
	//	{ eTile::Water,			-0.2f },
	//	{ eTile::DeepWater,		-0.5f },
	//};

	// TODO: clamp or re-rnage instead!? value between -1 and 1? multiply with something and convert to int? (truncate)? google convert perlin noise to tile type+
	/*for (const auto& [type, value] : noiseRanges)
	{
		if (aNoise > value)
		{
			return type;
		}
	}

	return eTile::Water;*/
}

Hi_Engine::Subtexture2D* GetSubtexture(eTile type) // TODO: check neighbours?
{
	static const std::unordered_map<eTile, Hi_Engine::SubtextureData> textures = {
		{ eTile::Grass,			{ "island_tileset", 3, 6 }},
		{ eTile::Sand,			{ "island_tileset", 1, 3 }},
		{ eTile::ShallowWater,  { "island_tileset", 1, 8 }},
		{ eTile::Water,			{ "island_tileset", 1, 8 }},
		{ eTile::DeepWater,		{ "island_tileset", 1, 8 }}, // NEEDED??
	};

	const auto& texture = textures.at(type);

	return &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource(texture);
}

glm::vec4 GetTileColor(eTile type)
{
	if (type == eTile::ShallowWater)
		return { 0.25f, 0.88f, 0.81f, 1.f };
	if (type == eTile::Water)
		return { 0.f, 0.69f, 0.63f, 1.f };
	if (type == eTile::DeepWater)
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

void MapGenerationSystem::Receive(Message& message)
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

void MapGenerationSystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;

	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();

	if (!player)
		return;

	auto* playerTransformComponent = player->GetComponent<TransformComponent>();

	auto coordinates = ConvertWorldPositionToMapChunkCoordinates(playerTransformComponent->CurrentPos);	// Todo, check all 4 corners of player (Get hitboxCollider)

	auto mapChunks = m_entityManager->FindAll<MapChunkComponent>();
	for (const auto& mapChunk : mapChunks)
	{
		auto* mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();
		if (mapChunkComponent->Coordinates == coordinates)
		{
			// Chunk already exist
			return;
		}
	}

	GenerateMapChunk(coordinates.x, coordinates.y);

	// TODO; remove/unload chunks?
}

void MapGenerationSystem::GenerateMapChunk(int xCoord, int yCoord)
{
	// MOVE ELSEWHERE? static in a function (GetNoise)?
	FastNoiseLite fastNoise;
	fastNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	fastNoise.SetFrequency(0.06f);
	//fastNoise.SetFrequency(0.006f);

	// Generate numbers first??

	auto* entity = m_entityManager->Create("map_chunk");

	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();
	auto* transformComponent = entity->GetComponent<TransformComponent>(); // Do it need a transform compoentn?

	mapChunkComponent->Coordinates = { xCoord, yCoord };

	float xPos = xCoord * (MapChunkComponent::TileCountPerSide * Tile::Size);
	float yPos = yCoord * (MapChunkComponent::TileCountPerSide * Tile::Size);
	transformComponent->CurrentPos = { xPos, yPos };

	for (unsigned height = 0; height < MapChunkComponent::TileCountPerSide; ++height)
	{
		for (unsigned width = 0; width < MapChunkComponent::TileCountPerSide; ++width)
		{
			float noise = fastNoise.GetNoise((float)xPos + (float)width, (float)yPos + float(height));

			Tile tile;
			tile.Coordinates = { width, height };
			tile.IsCollidable = false; // FIX!
			tile.Type = GetTileType(noise);

			mapChunkComponent->Tiles.push_back(tile);
		}
	}

	ApplyTextures(entity);

	PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity });
}

void MapGenerationSystem::ApplyTextures(Entity* entity) // Rename; texture map chunk?
{
	static const std::array<eDirectionalValue, 4> directionalValues = { eDirectionalValue::North, eDirectionalValue::West, eDirectionalValue::East, eDirectionalValue::South };

	auto* transformComponent = entity->GetComponent<TransformComponent>();
	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();

	for (int i = 0; i < mapChunkComponent->Tiles.size(); ++i)
	{
		auto& tile = mapChunkComponent->Tiles[i];

		if (tile.Type == eTile::Sand)
		{
			int baseValue = 0;

			for (const auto& directionalValue : directionalValues)
			{
				bool isEmptySpace = MapUtils::IsTileTypeInDirection(entity, i, directionalValue, eTile::ShallowWater);
				//if (MapUtils::GetTileTypeInDirection())
				baseValue += (int)directionalValue * isEmptySpace;
			}



			if (MapUtils::GetTileTypeInDirection(entity, i, eDirection::Down) == eTile::ShallowWater)
			{
				tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({"island_tileset", 3, 1 });
				//tile.Color = { 0.f, 0.3f, 0.5f, 1.f };
			}
			else if (MapUtils::GetTileTypeInDirection(entity, i, eDirection::Up) == eTile::ShallowWater)
			{
				tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "island_tileset", 5, 1 });
				//tile.Color = { 0.f, 0.3f, 0.5f, 1.f };
			}
			else if (MapUtils::GetTileTypeInDirection(entity, i, eDirection::Left) == eTile::ShallowWater)
			{
				tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "island_tileset", 4,0 });
				//tile.Color = { 0.f, 0.3f, 0.5f, 1.f };
			}
			else if (MapUtils::GetTileTypeInDirection(entity, i, eDirection::Right) == eTile::ShallowWater)
			{
				tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "island_tileset", 4,2 });
				//tile.Color = { 0.f, 0.3f, 0.5f, 1.f };
			}
			else
			{
				tile.Subtexture = GetSubtexture(tile.Type);
			}
		}
		else /*if (tile.Type == eTile::ShallowWater)*/
		{
			tile.Subtexture = GetSubtexture(tile.Type);
		}

		// Check if more optimized (dont have to do every frame?!)
		Hi_Engine::SpriteRenderData renderData;
		renderData.Color = GetTileColor(mapChunkComponent->Tiles[i].Type); // { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
		renderData.Subtexture = tile.Subtexture;
		auto currentPosition = transformComponent->CurrentPos;

		glm::vec3 position = { currentPosition.x, currentPosition.y, 0.f };
		position.x += tile.Coordinates.x * Tile::Size;
		position.y += tile.Coordinates.y * Tile::Size;
		renderData.Transform = { position, { 1.01f, 1.01f }, 0.f }; // TEMP Solution with scale at 1.01f
		mapChunkComponent->RenderData.push_back(renderData);

	}
}

void MapGenerationSystem::UnloadMapChunk()
{
	// TODO; need to save world state in map chunk (placed objects, etc).. (store changes done by the player)
}
