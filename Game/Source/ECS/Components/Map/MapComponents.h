#pragma once
#include "../Base/Component.h"
//#include "../../DataTypes/Structs.h"
#include <vector>
#include <Utility/Math/Vectors/Vector3.hpp>

namespace CU = CommonUtilities;

struct MapChunkComponent : public Component
{
	CU::Vector2<int>	Coordinates;
	// CU::Vector3<float>	m_position; - stored in TransformComponent
	std::vector<Tile>	Tiles;

	inline static unsigned TileCountPerSide; // Side length in tiles

	// TEMP
	bool IsEdgeChunk = false;

	// static unsigned		Width, Height;		// replace with size?? Transform instead?? what does size refere to?


	//	unsigned				m_chunkID;

	// neighbours??

	// HERE? or a new component...
	std::vector<Hi_Engine::SpriteRenderData> RenderData;
	bool IsRenderDataDirty; // ??
};