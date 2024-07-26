#pragma once
#include "../Base/System.h"


class MapGenerationSystem : public System, public Subscriber
{
public:
	MapGenerationSystem();
	~MapGenerationSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;

private:
	void GenerateMapChunk(int xCoord, int yCoord);
	void UnloadMapChunk();

	// ApplyTileSettings?
	void ApplyTextures(Entity entity); // RetileMapChunk - do in separate system?	TextureMappingSystem? -> creates holes. etc when digging?!
	void SetupMapEditor();

	void RegenerateMap();

	// Maybe?
};