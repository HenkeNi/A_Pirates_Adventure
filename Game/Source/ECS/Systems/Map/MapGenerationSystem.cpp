#include "Pch.h"
#include "MapGenerationSystem.h"
#include "Entities/EntityManager.h"
//#include "../Data/Constants.h"
#include "Constants.h"
#include "../Utility/Map/MapUtils.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Map/MapComponents.h"
// #include <FastNoiseLite.h>




std::unordered_map<eTimeOfDay, FVector4> GetTileColors(eTile type)
{
	std::unordered_map<eTimeOfDay, FVector4> colors;

	switch (type)
	{
	case eTile::Grass:

		break;
	case eTile::Sand:
		colors.insert(std::make_pair(eTimeOfDay::Dawn,	FVector4{ 0.9804f, 0.7725f, 0.5529f, 1.f }));
		colors.insert(std::make_pair(eTimeOfDay::Day,	FVector4{ 0.9569f, 0.8471f, 0.6706f, 1.f }));
		colors.insert(std::make_pair(eTimeOfDay::Dusk,  FVector4{ 0.89f, 0.68f, 0.42f, 1.f }));
		colors.insert(std::make_pair(eTimeOfDay::Night, FVector4{ 0.302f, 0.302f, 0.302f, 1.f }));
		break;
	case eTile::ShallowWater:
		break;
	case eTile::Water:
		break;
	case eTile::DeepWater:
		break;
	case eTile::Void:
		break;
	default:
		break;
	}
	return colors;
}


// WHere to store various tile settings? ResourceHolder TileSettings?
struct TileSettings
{
	std::string Identifier; //?? NEEDED?
	std::unordered_map<eTimeOfDay, FVector4> Colors;
	// ARray of subtextures??
	bool IsCollidable;
};




IVector2 ConvertWorldPositionToMapChunkCoordinates(const FVector2& worldPosition)
{
	static float chunkSize = Constants::MapChunkLength * Tile::Size;

	IVector2 coordinates;
	coordinates.x = (int)std::floor(worldPosition.x / chunkSize);
	coordinates.y = (int)std::floor(worldPosition.y / chunkSize);

	return coordinates;
}




struct TerrainSettings
{
	std::string Identifier;
	FVector2 NoiseRange;
};

eTile GetTileType(float noise)
{
	//int noiseValue = (int)(noise * 10);

	// std::cout << noise << "\n";

	static const std::unordered_map<eTile, float> tileHeightValues = {
	{ eTile::Grass,			0.4 },
	{ eTile::Sand,			0.2 },
	{ eTile::ShallowWater,	0.0 },
	{ eTile::Water,			-1.0 },
	{ eTile::DeepWater,		-3.0 },
	};

	for (const auto& [type, value] : tileHeightValues)
	{
		if (noise >= value)
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

//int GetMaskValue()

Hi_Engine::Subtexture2D* GetSubtexture(eTile type) // TODO: check neighbours?
{
	static const std::unordered_map<eTile, Hi_Engine::SubtextureData> textures = {
		{ eTile::Grass,			{ "island_tileset", 2, 6 }},
		{ eTile::Sand,			{ "island_tileset", 4, 3 }},
		{ eTile::ShallowWater,  { "island_tileset", 4, 8 }},
		{ eTile::Water,			{ "island_tileset", 4, 8 }},
		{ eTile::DeepWater,		{ "island_tileset", 4, 8 }}, // NEEDED??
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
	//if (type == eTile::Sand)
	//	return { 0.302f, 0.302f, 0.302f, 1.f };

	return { 1.f, 1.f, 1.f, 1.f };
}


MapGenerationSystem::MapGenerationSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this); // NewGameCreated instead?


	//Hi_Engine::NoiseGenerator::SetFrequency(0.01f);
	Hi_Engine::NoiseGenerator::SetFrequency(0.06f);
	Hi_Engine::NoiseGenerator::SetNoiseType(3);

#ifdef DEBUG

	SetupMapEditor();

#endif // DEBUG

}

MapGenerationSystem::~MapGenerationSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void MapGenerationSystem::Receive(Message& message)
{
	// Generate x amount of areas...

	//for (int y = 0; y < 3; ++y)
	{
	//	for (int x = 0; x < 3; ++x)
		{
			GenerateMapChunk(0, 0);
			//GenerateMapChunk(x, y);
		}
	}
}

void MapGenerationSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	// Todo; use camera bounds instead??
	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	if (!camera)
		return;

	//auto* transformComponent = camera->GetComponent<TransformComponent>();
	//auto* cameraComponent = camera->GetComponent<CameraComponent>();

	//static const FVector2 windowSize = { 1400.f, 800.f };
	//
	//float xPosition = transformComponent->CurrentPos.x - (cameraComponent->TargetOffset.x * windowSize.x);
	//float yPosition = transformComponent->CurrentPos.y - (cameraComponent->TargetOffset.y * windowSize.y);

	//auto coordinates = ConvertWorldPositionToMapChunkCoordinates({ xPosition, yPosition });	// Todo, check all 4 corners of player (Get hitboxCollider)


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
	auto* entity = m_entityManager->Create("map_chunk");

	auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();
	auto* transformComponent = entity->GetComponent<TransformComponent>(); // Do it need a transform compoentn?

	mapChunkComponent->Coordinates = { xCoord, yCoord };

	auto& currentPosition = transformComponent->CurrentPos;
	currentPosition.x = xCoord * (Constants::MapChunkLength * Tile::Size);
	currentPosition.y = yCoord * (Constants::MapChunkLength * Tile::Size);

	for (int i = 0; i < Constants::MapChunkSize; ++i)
	{
		int x, y;
		MapUtils::GetCoordinates(i, Constants::MapChunkLength, x, y);

		float noiseX = ((float)currentPosition.x / Tile::Size) + (float)x;
		float noiseY = ((float)currentPosition.y / Tile::Size) + (float)y;

		float noise = Hi_Engine::NoiseGenerator::GetNoise(noiseX, noiseY);

		Tile& tile = mapChunkComponent->Tiles[i];
		tile.Coordinates = { (unsigned)x, (unsigned)y };
		tile.IsTraversable = false; // FIX!
		tile.Type = GetTileType(noise);

		// tile.Color = { 1.f, noise, 1.f, 1.f };

		// float roundedValue = std::round(noise * 100.f) / 100.f;
	}

	ApplyTextures(entity);
	PostMaster::GetInstance().SendMessage({ eMessage::MapChunkGenerated, entity }); // send entity created instead?
}

void MapGenerationSystem::UnloadMapChunk()
{
	// TODO; need to save world state in map chunk (placed objects, etc).. (store changes done by the player)
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
			// get neighbors
			int bitmaskValue = 0;

			for (const auto& directionalValue : directionalValues)
			{
				bool isEmptySpace = MapUtils::IsTileTypeInDirection(entity, i, directionalValue, eTile::ShallowWater);
				
				if (isEmptySpace)	
					continue;
				//if (MapUtils::GetTileTypeInDirection())
				bitmaskValue += (int)directionalValue;
			}

			if (bitmaskValue != 0)
			{
				static const std::array<std::pair<int, int>, 16> sandTextures = { {
					{ 4, 3 }, { 4, 4 }, { 4, 4 }, { 2, 2 },
					{ 4, 4 }, { 2, 0 }, { 4, 4 }, { 2, 1 },
					{ 4, 4 }, { 4, 4 }, { 0, 2 }, { 1, 2 },
					{ 0, 0 }, { 1, 0 }, { 0, 1 }, { 4, 4 },
				}};
 
				tile.Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({"island_tileset", sandTextures[bitmaskValue].first, sandTextures[bitmaskValue].second });
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
		

		auto& sprite = mapChunkComponent->Sprites[i];
		sprite.Color = GetTileColor(mapChunkComponent->Tiles[i].Type); // { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
		sprite.Subtexture = tile.Subtexture;

		const auto& currentPosition = transformComponent->CurrentPos;
		glm::vec3 position = { currentPosition.x, currentPosition.y, 0.f };
		position.x += tile.Coordinates.x * Tile::Size;
		position.y += tile.Coordinates.y * Tile::Size;
		sprite.Transform = { position, { Tile::Size + 0.01f, Tile::Size + 0.01f }, 0.f }; // TEMP Solution with scale at 1.01f

	
		mapChunkComponent->Bounds.Init({ currentPosition.x, currentPosition.y }, { currentPosition.x + (10 * Tile::Size), currentPosition.y + (10 * Tile::Size) });
	}
}

void MapGenerationSystem::SetupMapEditor()
{
	Hi_Engine::ImGuiWindow imGuiWindow;
	imGuiWindow.Title = "Perlin Noise";
	imGuiWindow.Size = { 200.f, 200.f };
	imGuiWindow.Position = { 1400.f - imGuiWindow.Size.x, 200.f };
	imGuiWindow.Buttons.emplace_back([&]() { m_entityManager->DestroySelected<MapChunkComponent>(); }, "Clear Map");

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::CreateImGuiWindowRequest>(imGuiWindow);
}

void MapGenerationSystem::RegenerateMap()
{

}
