#pragma once
#include "../Base/Component.h"
//#include "../../DataTypes/Structs.h"
#include <vector>
//#include <Utility/Math/Vectors/Vector3.hpp>
#include <../Hi_Engine.h>
#include "Constants.h"

struct MapChunkComponent : public Component
{
	IVector2 Coordinates; // In world coordinates

	//std::vector<Tile>	Tiles;
	std::array<Tile, Constants::MapChunkSize> Tiles;
	std::array<bool, Constants::MapChunkSize> CollisionMap;

	// Todo, store tile types in chunk??


	// static constexpr unsigned SideLength;

	// HERE? or a new component...
	std::vector<Hi_Engine::SpriteRenderData> RenderData;
	bool IsRenderDataDirty; // ??
};