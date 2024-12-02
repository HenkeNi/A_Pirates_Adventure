#pragma once
#include "../Base/System.h"

// MapGenerationSystem
class MapSystem : public System, public Subscriber
{
public:
	MapSystem();
	~MapSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;

private:
	void GenerateMapChunk(int xCoord, int yCoord);
	void ApplyTileTextures(Entity entity); // RetileMapChunk - do in separate system?	TextureMappingSystem? -> creates holes. etc when digging?!

	void UnloadMapChunk();
	void LoadMapChunk();


	// ApplyTileSettings?
	void SetupMapEditor();

	void RegenerateMap();
};