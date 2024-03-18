#pragma once
#include "../../Base/System.h"

struct MapChunkComponent;

class MapRenderSystem : public System
{
public:
	MapRenderSystem();
	~MapRenderSystem();

	void Receive(Message& message)	override;
	void Draw()						override;

private:
	void DrawMapChunk(MapChunkComponent* mapChunk, const CU::Vector2<float>& position);


	// DO culling first... (before rendering, and maybe before some other systems...) -> maybe after movement system... (no need to update ai for enemies out of view)??
	// CullingSystem? Has Static functions? or not part of ECS? Move To Camera System?!!
	//std::vector<Entity*> PerformFrustumCulling(std::vector<Entity*>& someEntities);
};