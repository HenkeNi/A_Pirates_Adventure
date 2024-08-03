#pragma once
#include "Constants.h"
#include <../Hi_Engine.h>


struct MapChunkComponent
{
	std::array<Tile, Constants::MapChunkSize> Tiles;
	std::array<bool, Constants::MapChunkSize> CollisionMap;
	std::array<Hi_Engine::Sprite, Constants::MapChunkSize> Sprites;
	//std::vector<Hi_Engine::Sprite> Sprites;

	IVector2 Coordinates; // In world coordinates

	// Todo, store tile types in chunk??

	// static constexpr unsigned SideLength;

	// maybe its own component???
	Hi_Engine::Physics::AABB2D<float> Bounds;

	// HERE? or a new component...
	bool IsRenderDataDirty; // ??
};