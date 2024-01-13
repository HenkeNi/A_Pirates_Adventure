#pragma once
#include "../../Base/System.h"

class MapChunkComponent;

class MapRenderSystem : public System
{
public:
	MapRenderSystem();
	~MapRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;

private:
	void DrawMapChunk(MapChunkComponent* aMapChunk, const CU::Vector2<float>& aPosition);
};