#include "Pch.h"
#include "MapGenerator.h"


MapGenerator::MapGenerator()
{
}

MapGenerator::~MapGenerator()
{
}

std::vector<MapChunk> MapGenerator::GenerateStartArea()
{

	// Pass responsibility to Map? 
	unsigned tileSize = 1.f;
	std::vector<MapChunk> mapChunks;

	for (int col = 0; col < 5; ++col)
	{
		for (int row = 0; row < 5; ++row)
		{
			MapChunk chunk{};
			//chunk.SetPosition({ (float)col + chunk.m_chunkWidth * tileSize, 0.f, (float)row + chunk.m_chunkHeight * tileSize });
			chunk.SetPosition({ (float)col * (chunk.m_chunkWidth * tileSize),  0.f, (float)row * (chunk.m_chunkHeight * tileSize) });

			bool isLand = (col > 0 && col < 4) && (row > 0 && row < 4);
			chunk.m_isWater = !isLand;
			chunk.CreateTiles(isLand);

			mapChunks.push_back(chunk);

			// generate foilage here?
		}
	}

	return mapChunks;
}

void MapGenerator::GenerateFoilage()
{
}

void MapGenerator::GenerateEnvironment()
{
}