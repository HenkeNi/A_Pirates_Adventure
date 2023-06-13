#pragma once
#include "Base/System.h"

class MapChunk;

// Render map chunks..
class MapRenderSystem : public System
{
public:
	MapRenderSystem();
	~MapRenderSystem();

	void Receive(Message& aMsg)		override;
	void Draw()						override;

private:
	void RenderChunk(const MapChunk& aMapChunk);

	// Store chunks separately??
	// std::vector<Entity*> m_mapChunks;


	// Grid?? either by value or pointer to it => lives in OutworldScene, IndoorScene?

	class Map* m_map;
};

