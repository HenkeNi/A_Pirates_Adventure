#pragma once
#include "../Base/System.h"


class MapGenerationSystem : public System
{
public:
	MapGenerationSystem();
	~MapGenerationSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	void GenerateMapChunk(int xCoord, int yCoord);

	// ApplyTileSettings?
	void ApplyTextures(class Entity* anEntity); // RetileMapChunk - do in separate system?	TextureMappingSystem? -> creates holes. etc when digging?!


	// Maybe?
	void UnloadMapChunk();

};	