#pragma once
#include "Map.h"
#include "MapChunk.h"


// rename MapGenerationSystem?
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	//Map GenerateMap() const; 

	std::vector<MapChunk> GenerateStartArea();
	std::vector<MapChunk> GenerateMapChunks();	// take in a direction?


	// Generate cave?

private:
	void GenerateFoilage();
	void GenerateEnvironment();

};